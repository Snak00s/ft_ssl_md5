/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdecapitalize.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinton <tpinton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:13:13 by tpinton           #+#    #+#             */
/*   Updated: 2026/05/13 14:13:14 by tpinton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdecapitalize(char *str)
{
	int i = 0;
	while (str[i])
	{
		char c = str[i];
		if (c >= 65 && c <= 90)
			str[i] = c + 32;
		i++;
	}
	return (str);
}