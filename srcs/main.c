#include"ssl.h"

//parse all the flag of the command.
//return the idx "i" of the last flag
//in case of error, return "-i" to indicate which flag proc the error
static int	parse_arg(char **argv, const int argc, int *flags, t_list **arg)
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
					*flags |= SSL_PF;
					break;
				case 'q':
					*flags |= SSL_QF;
					break;
				case 'r':
					*flags |= SSL_RF;
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
			ssl_msg *message = ft_calloc(1, sizeof(ssl_msg));
			if (!message)
				return (0);
			message->arg = argv[i];
			message->type = ((is_string == 1) ? SSL_STRING : SSL_FILE);
			end_flag = ((is_string == 1) ? 0 : 1);
			is_string = 0;

			if (!*arg)
			{
				*arg = ft_lstnew(message);
				if (!*arg)
					return (0);
			}
			else
			{
				t_list *new = ft_lstnew(message);
				if (!new)
					return (0);
				ft_lstadd_back(arg, new);
			}
		}
		i++;
	}
	return (1);
}

//find and put in "current_algo" the corresponding hashing algorithm base on "name"
//this function need a list of algorythm (see 'hash_t' prototype) and the amount of entry the list have
//
//in case of error return 0
static int	find_hashing_algo(char *name, hash_t *current_algo, hash_t *algo_list, const size_t nbr_entry)
{
	current_algo->func = NULL;
	current_algo->name = NULL;
	for (size_t i = 0; i < nbr_entry; i++)
	{
		if (ft_strncmp(name, algo_list[i].name, ft_strlen((char *)algo_list[i].name)) == 0)
		{
			current_algo->func = algo_list[i].func;
			current_algo->name = algo_list[i].name;
			current_algo->print_name = algo_list[i].print_name;
			break;
		}
	}
	if (!current_algo->func)
	{
		str_bad_cmd(name);
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_list		*msg_list = NULL;
	
	if (argc < 2)
	{
		write(2, "usage: ft_ssl command [flags] [file/string]\n", 45);
		return (1);
	}

	hash_t	algo_list[] = {
		{"md5", "MD5", md5},
		{"sha256", "SHA256", sha256},
		{"whirlpool", "WHIRLPOOL", whirlpool}
	};

	hash_t	current_algo;
	if (!find_hashing_algo(argv[1], &current_algo, algo_list, sizeof(algo_list) / sizeof(*algo_list)))
		return (1);

	int flags = 0;
	int f_ind = parse_arg(argv, argc, &flags, &msg_list);
	if (f_ind <= 0)
	{
		if (f_ind == 0)
		{
			printf("Alloc Error\n");
			return (1);
		}
		invalid_param(argv[-f_ind], "flag");
		return (1);
	}

	if (!process_algo(msg_list, &current_algo, flags))
		return (free_lst(msg_list, 1), 1);

	free_lst(msg_list, 1);
	return (0);
}