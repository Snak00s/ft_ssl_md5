/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinton <tpinton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:36:35 by tpinton           #+#    #+#             */
/*   Updated: 2024/11/27 12:16:09 by tpinton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<stdlib.h>
# include<unistd.h>
# include<stdarg.h>
# include<stdio.h>

void	ft_putchar(char c, int *count);
void	ft_putstr(char *str, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putnbr_unsigned(unsigned int n, int *count);
void	ft_putnbr_base(unsigned int nbr, char *base, int *count);
void	ft_putnbr_base_long(unsigned long nbr, char *base, int *count);
void	ft_checkcond(char c, va_list param, int *count);
void	ft_print_p(va_list param, int *count);
int		ft_printf(const char *format, ...);
#endif