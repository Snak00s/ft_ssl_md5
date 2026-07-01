/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinton <tpinton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:16:56 by tpinton           #+#    #+#             */
/*   Updated: 2024/11/27 12:17:49 by tpinton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	ft_putchar(char c, int *count)
{
	(*count)++;
	write(1, &c, 1);
}

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (str[i])
	{
		ft_putchar(str[i], count);
		i++;
	}
}

void	ft_putnbr(int n, int *count)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		ft_putchar('-', count);
	}
	if (n <= 9)
	{
		c = '0' + n;
		ft_putchar(c, count);
	}
	else
	{
		ft_putnbr(n / 10, count);
		ft_putnbr(n % 10, count);
	}
}

void	ft_putnbr_unsigned(unsigned int n, int *count)
{
	char	c;

	if (n <= 9)
	{
		c = '0' + n;
		ft_putchar(c, count);
	}
	else
	{
		ft_putnbr_unsigned(n / 10, count);
		ft_putnbr_unsigned(n % 10, count);
	}
}

void	ft_print_p(va_list param, int *count)
{
	unsigned long	l;

	l = (unsigned long) va_arg(param, unsigned long);
	if (!l)
	{
		ft_putstr("(nil)", count);
		return ;
	}
	else
	{
		ft_putstr("0x", count);
		ft_putnbr_base_long(l, "0123456789abcdef", count);
	}
}
