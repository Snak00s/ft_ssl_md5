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

char *read_file(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Invalid file\n");
		return (NULL);
	}
	char *text = NULL;
	char *line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (NULL);
	}
	while (line)
	{
		text = ft_strjoin_free(text, line);
		if (!text)
		{
			close(fd);
			return (free(line), NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (text);
}

int	find_hashing_algo(char *name, hash_t *algo, hash_t *algo_list, size_t nbr_entry)
{
	algo->func = NULL;
	algo->name = NULL;
	for (size_t i = 0; i < nbr_entry; i++)
	{
		if (ft_strncmp(name, algo_list[i].name, ft_strlen((char *)algo_list[i].name)) == 0)
		{
			algo->func = algo_list[i].func;
			algo->name = algo_list[i].name;
			break;
		}
	}
	if (!algo->func)
	{
		str_bad_cmd(name);
		return (0);
	}
	return (1);
}

int process_algo(char **arg, int idx_begin, int idx_end, hash_t *algo)
{
	for (int i = idx_begin; i < idx_end; i++)
	{
		char *text = read_file(arg[i]);
		if (!text)
			return (0);
		char *digest = algo->func(text);
		if (!digest)
		{
			free(text);
			return (0);
		}
		write(1, digest, ft_strlen(digest));
		write(1, "\n", 1);
		free(text);
		free(digest);
	}
	return (1);
}

int main(int argc, char **argv)
{
	ssl_flags	flags;
	ft_memset(&flags, 0, sizeof(flags));

	if (argc < 2)
	{
		write(2, "usage: ft_ssl command [flags] [file/string]\n", 45);
		return (1);
	}

	hash_t	algo_list[] = {
		{"md5", md5},
		{"sha256", sha256},
	};

	hash_t	algo;

	if (!find_hashing_algo(argv[1], &algo, algo_list, sizeof(algo_list) / sizeof(*algo_list)))
		return (1);

	int f_ind = parse_flags(argv, argc, &flags);
	if (f_ind < 0)
	{
		invalid_thing(argv[-f_ind], "flag");
		return (1);
	}

	if (!process_algo(argv, f_ind, argc, &algo))
		return (1);

	return (0);
}