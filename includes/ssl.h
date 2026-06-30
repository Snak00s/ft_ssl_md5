#ifndef SSL_H
# define SSL_H

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef struct ssl_flags {
	unsigned char	p_flag;
	unsigned char	q_flag;
	unsigned char	r_flag;
	unsigned char	s_flag;
} ssl_flags;


//md5
char	*md5(void);


//sha256
char	*sha256(void);

//utils
void	str_bad_cmd(char *cmd);
size_t	ft_strlen(char *str);
void	*ft_memset(void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
uint64_t	ft_swapLongEndian(uint64_t nbr);
uint32_t	ft_swapIntEndian(uint32_t nbr);
uint16_t	ft_swapShortEndian(uint16_t nbr);


#endif