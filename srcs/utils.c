#include"ssl.h"

size_t ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && (s1[i] || s2[i]) && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (size && nmemb * size > SIZE_MAX)
		return (NULL);
	tab = (void *)malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

uint64_t	ft_swapLongEndian(uint64_t nbr)
{
	uint8_t b1 = (uint8_t)(nbr >> 56);
	uint8_t b2 = (uint8_t)(nbr >> 48);
	uint8_t b3 = (uint8_t)(nbr >> 40);
	uint8_t b4 = (uint8_t)(nbr >> 32);
	uint8_t b5 = (uint8_t)(nbr >> 24);
	uint8_t b6 = (uint8_t)(nbr >> 16);
	uint8_t b7 = (uint8_t)(nbr >> 8);
	uint8_t b8 = (uint8_t)(nbr);

	uint64_t newnbr = ((uint64_t)b8 << 56) | ((uint64_t)b7 << 48) | ((uint64_t)b6 << 40) | ((uint64_t)b5 << 32) | ((uint64_t)b4 << 24) | ((uint64_t)b3 << 16) | ((uint64_t)b2 << 8) | ((uint64_t)b1);

	return (newnbr);
}

uint32_t	ft_swapIntEndian(uint32_t nbr)
{
	uint8_t b1 = (uint8_t)(nbr >> 24);
	uint8_t b2 = (uint8_t)(nbr >> 16);
	uint8_t b3 = (uint8_t)(nbr >> 8);
	uint8_t b4 = (uint8_t)(nbr);

	uint32_t newnbr = ((uint32_t)b4 << 24) | ((uint32_t)b3 << 16) | ((uint32_t)b2 << 8) | ((uint32_t)b1);

	return (newnbr);
}

uint16_t	ft_swapShortEndian(uint16_t nbr)
{
	uint8_t b1 = (uint8_t)(nbr >> 8);
	uint8_t b2 = (uint8_t)(nbr);

	uint16_t newnbr = ((uint16_t)b2 << 8) | ((uint16_t)b1);

	return (newnbr);
}