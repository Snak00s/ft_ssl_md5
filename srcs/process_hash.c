#include "ssl.h"

static int hash_string(ssl_msg *thing, hash_t *algo, ssl_flags *flags)
{
	char *digest = algo->func(thing->arg);
	if (!digest)
		return (0);
	print_hash(algo->print_name, digest, thing->arg, flags->sum_flags, thing->type);
	free(digest);

	return (1);
}

static int hash_file(ssl_msg *thing, hash_t *algo, ssl_flags *flags)
{
	char *msg = NULL;
	if (!read_file(thing->arg, &msg))
			return (0);
	char *digest = algo->func(msg);
	if (!digest)
	{
		free(msg);
		return (0);
	}
	print_hash(algo->print_name, digest, thing->arg, flags->sum_flags, thing->type);
	free(msg);
	free(digest);

	return (1);
}

//if no file / string -> try to read stdin
//if stdin and file / string but no -p -> only read file / string
//if ........................... and -p -> read stdin + file / string
int process_algo(t_list *message, hash_t *algo, ssl_flags *flags)
{
	int (*hash_func[2])(ssl_msg *, hash_t *, ssl_flags *) = {hash_string, hash_file};

	if (!message || flags->p_flag)
	{
		char *msg = NULL;
		read_fd(0, &msg);
		char *digest = algo->func(msg);
		if (!digest)
		{
			free(msg);
			return (0);
		}
		char *arg = flags->p_flag ? msg : "stdin";
		print_stdin(digest, arg, flags);
		free(msg);
		free(digest);
	}
	t_list *temp = message;
	while (temp)
	{
		ssl_msg	*thing = (ssl_msg *)temp->content;
		if (!hash_func[thing->type](thing, algo, flags))
			ft_printf("ft_ssl: %s: %s: No such file or directory\n", algo->name, thing->arg);
		temp = temp->next;
	}
	return (1);
}