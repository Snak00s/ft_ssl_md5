/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinton <tpinton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:03:31 by tpinton           #+#    #+#             */
/*   Updated: 2025/03/20 14:37:39 by tpinton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

void	ft_checkcond(char c, va_list param, int *count)
{
	if (c == 'c')
		ft_putchar((char) va_arg(param, int), count);
	else if (c == 's')
		ft_putstr((char *) va_arg(param, char *), count);
	else if (c == 'p')
		ft_print_p(param, count);
	else if (c == 'd')
		ft_putnbr((int) va_arg(param, int), count);
	else if (c == 'i')
		ft_putnbr((int) va_arg(param, int), count);
	else if (c == 'u')
		ft_putnbr_unsigned((unsigned int) va_arg(param, unsigned int), count);
	else if (c == 'x')
		ft_putnbr_base((int) va_arg(param, int), "0123456789abcdef", count);
	else if (c == 'X')
		ft_putnbr_base((int) va_arg(param, int), "0123456789ABCDEF", count);
	else if (c == '%')
		ft_putchar(c, count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	param;

	i = 0;
	if (!format)
		return (-1);
	va_start(param, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			ft_checkcond(*format, param, &i);
		}
		else
		{
			ft_putchar(*format, &i);
		}
		format++;
	}
	va_end(param);
	return (i);
}
/*
int	main(void)
{
	int		i;

	i = ft_printf("%s");
	ft_printf(0);
	printf(0);
	return(0);
}*/