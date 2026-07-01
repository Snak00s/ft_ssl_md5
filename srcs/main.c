#include"ssl.h"

int	parse_flags(char **argv, int argc, ssl_flags *flags)
{
	int i = 2;
	while (i < argc)
	{
		if (*argv[i] == '-')
		{
			char *str = argv[i];
			switch (str[1])
			{
				case 'p':
					flags->p_flag = 1;
					break;
				case 'q':
					flags->q_flag = 1;
					break;
				case 'r':
					flags->r_flag = 1;
					break;
				case 's':
					flags->s_flag = 1;
					break;
				default:
					return(-i);
			}
		}
		else
			break;
		i++;
	}
	return (i);
}

int main(int argc, char **argv)
{
	ssl_flags	flags;
	ft_memset(&flags, 0, sizeof(flags));

	//---parsing
	if (argc < 2)
	{
		write(2, "usage: ft_ssl command [flags] [file/string]\n", 45);
		return (1);
	}

	int f_ind = parse_flags(argv, argc, &flags);

	if (f_ind < 0)
	{
		f_ind = -f_ind;
		write(1, "ft_ssl: Error: \'", 17);
		write(1, argv[f_ind], ft_strlen(argv[f_ind]));
		write(1, "\' is an invalid flag.\n", 23);
		return (1);
	}
	//---

	hash_t	algo[] = {
		{"md5", md5},
		{"sha256", sha256},
	};

	hashfunc_t	function_caller = NULL;
	char		*algo_name = NULL;

	size_t nbr_entry = sizeof(algo) / sizeof(*algo);
	for (size_t i = 0; i < nbr_entry; i++)
	{
		if (ft_strncmp(argv[1], algo[i].name, ft_strlen((char *)algo[i].name)) == 0)
		{
			function_caller = algo[i].func;
			algo_name = (char *)algo[i].name;
			break;
		}
	}

	if (!function_caller)
	{
		write(1, "ft_ssl: Error: \'", 17);
		write(1, argv[1], ft_strlen(argv[1]));
		write(1, "\' is an invalid command.\n", 25);
		return (1);
	}

	(void)algo_name;
	for (int i = f_ind; i < argc; i++)
	{
		char *digest = function_caller(argv[i]);
		if (!digest)
			return (1);
		write(1, digest, ft_strlen(digest));
		write(1, "\n", 1);
		free(digest);
	}

	return (0);
}