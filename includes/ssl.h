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
	char		*name;
	char		*print_name;
	hashfunc_t	func;
} hash_t;

typedef struct ssl_flags {
	unsigned char	p_flag;
	unsigned char	q_flag;
	unsigned char	r_flag;
} ssl_flags;

enum ssl_msg_type {
	SSL_STRING,
	SSL_FILE
};

typedef struct ssl_msg {
	int				type;
	char			*arg;
} ssl_msg;

//md5
char		*md5(char *str);

//process hash
int			process_algo(t_list *message, hash_t *algo, ssl_flags *flags);

//sha256
char		*sha256(char *str);

//whirlpool
char		*whirlpool(char *str);

//utils
void		str_bad_cmd(char *cmd);
void		hexaitoa(char *buff, uint32_t byte);
void		hexaton(char *hexa, size_t len);
uint32_t	set32intbit(unsigned char *str);
uint32_t	leftRotate(uint32_t n, uint32_t t);
uint32_t	rightRotate(uint32_t value, uint32_t n);
void		invalid_thing(char *arg, char *type);
int			read_fd(int fd, char **buff);
int			read_file(char *filename, char **buff);
void		free_lst(t_list *s_env, int mode);


#endif