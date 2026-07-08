#include"ssl.h"

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

void	print_hash(char *algo_name, char *digest, char *arg, int sum_flags, int type)
{
	void	(*print[])(char *, char *, char *, int) = {print_hash_nf, print_hash_r, print_hash_q, print_hash_q};
	print[flag_to_idx(sum_flags)](algo_name, digest, arg, type);

	return ;
}