#include"ssl.h"


//parse all the flag of the command.
//return the idx "i" of the last flag
//in case of error, return "-i" to indicate which flag proc the error
static int	parse_flags(char **argv, int argc, ssl_flags *flags)
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


//read a file with the given "fd" and put the result inside "buff"
//"buff" will be allocated inside the fonction
//
//in case of error, this function return 0
static int	read_fd(int fd, char **buff)
{
	char *line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		*buff = ft_strjoin_free(*buff, line);
		if (!*buff)
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

//read a file with the given "filename" and put the result inside "buff"
//"buff" will be allocated inside the fonction
//
//in case of error, this function return 0
static int	read_file(char *filename, char **buff)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(1, "Invalid file\n", 14);
		return (0);
	}
	char *line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	while (line)
	{
		*buff = ft_strjoin_free(*buff, line);
		if (!*buff)
		{
			close(fd);
			return (free(line), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

//find and put in "algo" the corresponding hashing algorithm base on "name"
//this function need a list of algorythm (see 'hash_t' prototype) and the amount of entry the list have
//
//in case of error return 0
static int	find_hashing_algo(char *name, hash_t *algo, hash_t *algo_list, size_t nbr_entry)
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

void	print_result(const char *algo_name, char *digest, char *arg, ssl_flags *flags)
{
	(void)flags;
	if (flags->r_flag)
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

//if no file / string -> try to read stdin
//if stdin and file / string but no -p -> only read file / string
//if ........................... and -p -> read stdin + file / string
static int process_algo(char **arg, int idx_begin, int idx_end, hash_t *algo, ssl_flags *flags)
{
	if (idx_begin == idx_end || flags->p_flag)
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
	for (int i = idx_begin; i < idx_end; i++)
	{
		char *msg = NULL;
		if (!read_file(arg[i], &msg))
			return (0);
		char *digest = algo->func(msg);
		if (!digest)
		{
			free(msg);
			return (0);
		}
		print_result(algo->name, digest, arg[i], flags);
		free(msg);
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

	if (!process_algo(argv, f_ind, argc, &algo, &flags))
		return (1);

	return (0);
}