/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinton <tpinton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:13:17 by tpinton           #+#    #+#             */
/*   Updated: 2026/05/13 14:18:22 by tpinton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strcapitalize(char *str)
{
	int i = 0;
	while (str[i])
	{
		char c = str[i];
		if (c >= 97 && c <= 122)
			str[i] = c - 32;
		i++;
	}
	return (str);
}