#include"ssl.h"

int	parse_flags(char **argv, int argc, ssl_flags *flags)
{
	int i = 0;
	while (i < argc)
	{
		if (*argv[i] == '-')
		{
			char *str = argv[i];
			if (ft_strlen(str) != 2)
				return (0);

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
				return(0);
			}
		}
		i++;
	}
	return (1);
}

int main(int argc, char **argv)
{
	ssl_flags	flags;
	ft_memset(&flags, 0, sizeof(flags));

	// char *(*cmd[2]) (void) = {md5, sha256};

	if (argc < 2) {
		write(2, "usage: ft_ssl command [flags] [file/string]\n", 45);
		return (1);
	}

	if (!parse_flags(argv, argc, &flags)) {
		write(2, "Error: invalid argument.\n", 26);
		return (1);
	}

	md5();

	return (0);
}