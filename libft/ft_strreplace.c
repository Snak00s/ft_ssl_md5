#include"libft.h"

char *ft_strreplace(char *str, const char *replace, int (*cond)(char))
{
	int		i = 0;
	int		rep_len = ft_strlen(replace);
	char	*new_str = NULL;

	int nbr_replace = 0;
	while (str[i])
	{
		if (cond(str[i]))
			nbr_replace++;
		i++;
	}

	if (!nbr_replace || !rep_len)
		return (ft_strdup(str));

	int new_len = ft_strlen(str) + nbr_replace * rep_len - nbr_replace + 1;
	new_str = ft_calloc(new_len, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	int offset = 0;
	while (str[i])
	{
		new_str[i + offset] = str[i];
		if (cond(str[i]))
		{
			ft_memcpy(new_str + offset + i, replace, rep_len);
			offset += rep_len - 1;
		}
		i++;
	}
	return (new_str);
}