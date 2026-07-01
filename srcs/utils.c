#include"ssl.h"

static char *help()
{
	return ("Commands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n");
}

void str_bad_cmd(char *cmd)
{
	char *msg = help();
	write(2, "ft_ssl: Error: \'", 17);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\' is an invalid command.\n\n", 27);
	write(2, msg, ft_strlen(msg));
}

void	hexaton(char *hexa, size_t len)
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

uint32_t leftRotate(uint32_t n, uint32_t t)
{
    return ((n << t) | (n >> (32 - t)));
}