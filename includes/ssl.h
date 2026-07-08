#ifndef SSL_H
# define SSL_H

#include"../libft/libft.h"
#include"../libft/get_next_line_bonus.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#define SSL_RF 0b0000000000000001
#define SSL_QF 0b0000000000000010
#define SSL_PF 0b0000000000000100

typedef char *(*hashfunc_t)(char *);

typedef struct hash_t {
	char		*name;
	char		*print_name;
	hashfunc_t	func;
} hash_t;

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

//sha256
char		*sha256(char *str);

//whirlpool
char		*whirlpool(char *str);

//--------------------------------

//process hash
int			process_algo(t_list *msg_list, hash_t *current_algo, int flags);

//print hash
void		print_stdin(char *digest, char *arg, int flags);
void		print_hash(char *algo_name, char *digest, char *arg, int flags, int type);
int			flag_to_idx(int flags, int unwanted_flags);

//hash utils
void		hexaitoa(char *buff, uint32_t byte);
uint32_t	set32intbit(unsigned char *str);
uint32_t	leftRotate(uint32_t n, uint32_t t);
uint32_t	rightRotate(uint32_t value, uint32_t n);

//utils
int			read_fd(int fd, char **buff);
int			read_file(char *filename, char **buff);
void		free_lst(t_list *s_env, int mode);

void		str_bad_cmd(char *cmd);
void		invalid_param(char *arg, char *type);

#endif