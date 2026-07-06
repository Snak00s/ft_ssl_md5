#include"ssl.h"

//parse all the flag of the command.
//return the idx "i" of the last flag
//in case of error, return "-i" to indicate which flag proc the error
static int	parse_arg(char **argv, const int argc, ssl_flags *flags, t_list **arg)
{
	int is_string = 0;
	int end_flag = 0;

	int i = 2;
	while (i < argc)
	{
		if (*argv[i] == '-' && end_flag == 0)
		{
			char *str = argv[i];
			if (ft_strlen(str) != 2)
				return (-i);
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
					is_string = 1;
					break;
				default:
					return(-i);
			}
		}
		else
		{
			ssl_msg *thing = ft_calloc(1, sizeof(ssl_msg));
			if (!thing)
				return (0);
			thing->arg = argv[i];
			thing->type = ((is_string == 1) ? SSL_STRING : SSL_FILE);
			end_flag = ((is_string == 1) ? 0 : 1);
			is_string = 0;

			if (!*arg)
			{
				*arg = ft_lstnew(thing);
				if (!*arg)
					return (0);
			}
			else
			{
				t_list *new = ft_lstnew(thing);
				if (!new)
					return (0);
				ft_lstadd_back(arg, new);
			}
		}
		i++;
	}
	return (1);
}

//find and put in "algo" the corresponding hashing algorithm base on "name"
//this function need a list of algorythm (see 'hash_t' prototype) and the amount of entry the list have
//
//in case of error return 0
static int	find_hashing_algo(char *name, hash_t *algo, hash_t *algo_list, const size_t nbr_entry)
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

int main(int argc, char **argv)
{
	ssl_flags	flags;
	t_list		*message = NULL;
	
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

	ft_memset(&flags, 0, sizeof(flags));
	int f_ind = parse_arg(argv, argc, &flags, &message);
	if (f_ind <= 0)
	{
		if (f_ind == 0)
			printf("Alloc Error\n");
		invalid_thing(argv[-f_ind], "flag");
		return (1);
	}

	if (!process_algo(message, &algo, &flags))
		return (free_lst(message, 1), 1);

	free_lst(message, 1);
	return (0);
}