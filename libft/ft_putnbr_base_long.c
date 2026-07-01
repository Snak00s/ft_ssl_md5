/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_long.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinton <tpinton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:36:36 by tpinton           #+#    #+#             */
/*   Updated: 2026/05/13 13:01:36 by tpinton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static int	base_cond(char *str, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (size <= 1)
	{
		return (0);
	}
	while (str[i] != '\0')
	{
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[j] == str[i])
			{
				return (0);
			}
			j++;
		}
		if (str[i] == '-' || str[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

void	ft_putnbr_base_long(unsigned long nbr, char *base, int *count)
{
	unsigned long	i;
	unsigned long	nombre;

	i = 0;
	nombre = nbr;
	while (base[i] != '\0')
		i++;
	if (base_cond(base, i) == 0)
		return ;
	// if (nombre < 0)
	// {
	// 	ft_putchar('-', count);
	// 	nombre = nombre * -1;
	// }
	if (nombre < i)
	{
		ft_putchar(base[nombre], count);
	}
	if (nombre >= i)
	{
		ft_putnbr_base_long(nombre / i, base, count);
		ft_putnbr_base_long(nombre % i, base, count);
	}
}
/*
int	main(void)
{
	int	n;
	char	chaine[] = "0123456789abcdef";

	n = -2147483648;
	ft_putnbr_base_long(n, chaine);
	return(0);
}
*/
