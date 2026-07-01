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
