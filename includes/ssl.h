#ifndef SSL_H
# define SSL_H

#include"../libft/libft.h"
#include"../libft/get_next_line_bonus.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

typedef char *(*hashfunc_t)(char *);

typedef struct hash_t {
	const char	*name;
	hashfunc_t	func;
} hash_t;

typedef struct ssl_flags {
	unsigned char	p_flag;
	unsigned char	q_flag;
	unsigned char	r_flag;
	unsigned char	s_flag;
} ssl_flags;


//md5
char	*md5(char *str);


//sha256
char	*sha256(char *str);

//utils
void		str_bad_cmd(char *cmd);
void		hexaitoa(char *buff, uint32_t byte);
void		hexaton(char *hexa, size_t len);
uint32_t	set32intbit(unsigned char *str);
uint32_t	leftRotate(uint32_t n, uint32_t t);


#endif