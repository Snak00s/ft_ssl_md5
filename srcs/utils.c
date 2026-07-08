#include"ssl.h"

static char *help()
{
	return ("Commands:\nmd5\nsha256\nwhirlpool\n\nFlags:\n-p -q -r -s\n");
}

void str_bad_cmd(char *cmd)
{
	char *msg = help();
	write(2, "ft_ssl: Error: \'", 17);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\' is an invalid command.\n\n", 27);
	write(2, msg, ft_strlen(msg));
}

void	invalid_param(char *arg, char *type)
{
	const int size = 34 + ft_strlen(arg) + ft_strlen(type);
	char err_msg[size + 1];
	ft_memset(err_msg, 0, size + 1);
	ft_strlcat(err_msg, "ft_ssl: Error: \'", size + 1);
	ft_strlcat(err_msg, arg, size + 1);
	ft_strlcat(err_msg, "\' is an invalid ", size + 1);
	ft_strlcat(err_msg, type, size + 1);
	ft_strlcat(err_msg, ".\n", size + 1);
	write(1, err_msg, size);
}

static void	hexaton(char *hexa, size_t len)
{
	size_t	i = 0;
	while (i <= len / 2)
	{
		char c = hexa[i];
		hexa[i] = hexa[len - i];
		hexa[len - i] = c;
		i++;
	}
}

void	hexaitoa(char *buff, uint32_t byte)
{
	char set[] = "0123456789abcdef";
	char sample[100];
	ft_memset(sample, 0, 100);

	int i = 0;
	uint32_t val = byte;
	while (val)
	{
		uint32_t reste = val % 16;
		sample[i++] = set[reste];
		val /= 16;
	}
	if (byte == 0)
	{
		sample[i++] = '0';
		sample[i++] = '0';
	}
	else if (byte < 16)
		sample[i++] = '0';
	hexaton(sample, i - 1);
	ft_memcpy(buff, sample, 2);
	return ;
}

uint32_t set32intbit(unsigned char *str)
{
	uint8_t b1 = (uint8_t)(str[0]);
	uint8_t b2 = (uint8_t)(str[1]);
	uint8_t b3 = (uint8_t)(str[2]);
	uint8_t b4 = (uint8_t)(str[3]);

	uint32_t newnbr = ((uint32_t)b4 << 24) | ((uint32_t)b3 << 16) | ((uint32_t)b2 << 8) | ((uint32_t)b1);

	return (newnbr);
}

uint32_t leftRotate(uint32_t value, uint32_t n)
{
    return ((value << n) | (value >> (32 - n)));
}

uint32_t rightRotate(uint32_t value, uint32_t n)
{
	return ((value >> n) | (value << (32 - n)));
}

void	free_lst(t_list *s_env, int mode)
{
	t_list	*temp;

	if (!s_env)
		return ;
	while (s_env)
	{
		temp = s_env;
		s_env = s_env->next;
		if (mode == 1)
			free(temp->content);
		free(temp);
	}
	return ;
}

int flag_to_idx(int flags, int unwanted_flags)
{
	switch (flags & (~unwanted_flags))
	{
		case SSL_RF:							return(1);
		case SSL_QF:							return(2);
		case (SSL_QF | SSL_RF):					return(3);
		case SSL_PF:							return(4);
		case (SSL_PF | SSL_RF):					return(5);
		case (SSL_PF | SSL_QF):					return(6);
		case (SSL_PF | SSL_RF | SSL_QF):		return(7);
	}
	return (0);
}