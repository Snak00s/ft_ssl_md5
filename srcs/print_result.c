#include"ssl.h"

static int is_returnline(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

static void	print_hash_stdin_nf(char *digest, char *arg)
{
	ft_printf("(%s)= %s\n", arg, digest);

	return ;
}

static void	print_hash_stdin_p(char *digest, char *arg)
{
	char *trim_arg = ft_strtrim(arg, "\n");
	if (!trim_arg)
		return ;
	char *formated_arg = ft_strreplace(trim_arg, "\\n", is_returnline);
	if (!formated_arg)
		return ;
	free(trim_arg);
	ft_printf("(\"%s\")= %s\n", formated_arg, digest);
	free(formated_arg);

	return ;
}

static void	print_hash_stdin_q(char *digest, char *arg)
{
	(void)arg;
	write(1, digest, ft_strlen(digest));
	write(1, "\n", 1);

	return ;
}

static void	print_hash_stdin_pqr(char *digest, char *arg)
{
	write(1, arg, ft_strlen(arg));
	print_hash_stdin_q(digest, arg);

	return ;
}

void	print_stdin(char *digest, char *arg, int flags)
{

	void	(*print[])(char *, char *) = {
		print_hash_stdin_nf,
		print_hash_stdin_nf,
		print_hash_stdin_q,
		print_hash_stdin_nf,
		print_hash_stdin_p,
		print_hash_stdin_p,
		print_hash_stdin_q,
		print_hash_stdin_pqr
	};

	int idx = flag_to_idx(flags, 0);
	print[idx](digest, arg);
}

//-----------------------------------------------------------------------

static void	print_hash_nf(char *algo_name, char *digest, char *arg, int type)
{
	if (type == SSL_FILE)
		ft_printf("%s (%s) = %s\n", algo_name, arg, digest);
	else
		ft_printf("%s (\"%s\") = %s\n", algo_name, arg, digest);

	return ;
}

static void	print_hash_r(char *algo_name, char *digest, char *arg, int type)
{
	(void)algo_name;
	if (type == SSL_FILE)
		ft_printf("%s %s\n", digest, arg);
	else
		ft_printf("%s \"%s\"\n", digest, arg);

	return ;
}

static void	print_hash_q(char *algo_name, char *digest, char *arg, int type)
{
	(void)algo_name, (void)arg, (void)type;
	ft_printf("%s\n", digest);

	return ;
}

int	find_print_func(hash_t *current_algo, int flags)
{
	void	(*print[])(char *, char *, char *, int) = {print_hash_nf, print_hash_r, print_hash_q, print_hash_q};

	size_t idx = flag_to_idx(flags, SSL_PF);

	if (idx >= sizeof(print) / 8 || !print[idx])
		return (0);

	current_algo->print_func = print[idx];
	return (1);
}