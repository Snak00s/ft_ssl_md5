#include "ssl.h"

void	print_result(char *algo_name, char *digest, char *arg, ssl_flags *flags)
{
	if (flags->q_flag)
		ft_printf("%s\n", digest);
	else if (flags->r_flag)
		ft_printf("%s %s\n", digest, arg);
	else
		ft_printf("%s (%s) = %s\n", algo_name, arg, digest);
	return ;
}

void	print_stdin(char *digest, char *arg, ssl_flags *flags)
{
	if (flags->q_flag)
	{
		write(1, digest, ft_strlen(digest));
		write(1, "\n", 1);
	}
	else if (flags->p_flag)
	{
		char *formated_arg = ft_strtrim(arg, "\n");
		if (!formated_arg)
			return ;
		ft_printf("(\"%s\")= %s\n", formated_arg, digest);
		free(formated_arg);
	}
	else
		ft_printf("(%s)= %s\n", arg, digest);
}

static int hash_string(ssl_msg *thing, hash_t *algo, ssl_flags *flags)
{
	char *digest = algo->func(thing->arg);
	if (!digest)
		return (0);
	print_result(algo->print_name, digest, thing->arg, flags);
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
	print_result(algo->print_name, digest, thing->arg, flags);
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