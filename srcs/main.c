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

char *read_file(int fd)
{
	char *text = NULL;
	char *line = get_next_line(fd);
	if (!line)
		return (NULL);
	while (line)
	{
		text = ft_strjoin_free(text, line);
		if (!text)
			return (free(line), NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (text);
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
		invalid_thing(argv[-f_ind], "flag");
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
		invalid_thing(argv[1], "command");
		return (1);
	}

	(void)algo_name;
	for (int i = f_ind; i < argc; i++)
	{
		int fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			printf("Invalid file\n");
			continue;
		}
		char *text = read_file(fd);
		if (!text)
		{
			close(fd);
			return (1);
		}
		close(fd);
		char *digest = function_caller(text);
		if (!digest)
		{
			free(text);
			return (1);
		}
		write(1, digest, ft_strlen(digest));
		write(1, "\n", 1);
		free(text);
		free(digest);
	}

	return (0);
}