#include "ssl.h"

//read a file with the given "fd" and put the result inside "buff"
//"buff" will be allocated inside the fonction
//
//in case of error, this function return 0
int	read_fd(int fd, char **buff)
{
	char *line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		*buff = ft_strjoin_free(*buff, line);
		if (!*buff)
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

//read a file with the given "filename" and put the result inside "buff"
//"buff" will be allocated inside the fonction
//
//in case of error, this function return 0
int	read_file(char *filename, char **buff)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	char *line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	while (line)
	{
		*buff = ft_strjoin_free(*buff, line);
		if (!*buff)
		{
			close(fd);
			return (free(line), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
