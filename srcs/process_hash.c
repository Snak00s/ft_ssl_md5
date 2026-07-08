#include "ssl.h"

static int hash_string(ssl_msg *message, hash_t *current_algo, int flags)
{
	char *digest = current_algo->func(message->arg);
	if (!digest)
		return (0);

	print_hash(current_algo->print_name, digest, message->arg, flags, message->type);
	free(digest);

	return (1);
}

static int hash_file(ssl_msg *message, hash_t *current_algo, int flags)
{
	char *to_crypt = NULL;
	if (!read_file(message->arg, &to_crypt))
			return (0);

	char *digest = current_algo->func(to_crypt);
	if (!digest)
	{
		free(to_crypt);
		return (0);
	}

	print_hash(current_algo->print_name, digest, message->arg, flags, message->type);
	free(to_crypt);
	free(digest);

	return (1);
}

//if no file / string -> try to read stdin
//if stdin and file / string but no -p -> only read file / string
//if ........................... and -p -> read stdin + file / string
int process_algo(t_list *msg_list, hash_t *current_algo, int flags)
{
	int (*hash_func[2])(ssl_msg *, hash_t *, int) = {hash_string, hash_file};

	if (!msg_list || flags & SSL_PF)
	{
		char *to_crypt = NULL;
		read_fd(0, &to_crypt);
		char *digest = current_algo->func(to_crypt);
		if (!digest)
		{
			free(to_crypt);
			return (0);
		}
		char *arg = (flags & SSL_PF) ? to_crypt : "stdin";
		print_stdin(digest, arg, flags);
		free(to_crypt);
		free(digest);
	}

	t_list *temp = msg_list;
	while (temp)
	{
		ssl_msg	*message = (ssl_msg *)temp->content;
		if (!hash_func[message->type](message, current_algo, flags))
			ft_printf("ft_ssl: %s: %s: No such file or directory\n", current_algo->name, message->arg);
		temp = temp->next;
	}
	return (1);
}