/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:50:27 by pscarcin          #+#    #+#             */
/*   Updated: 2026/01/29 03:02:28 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_handle_specifier(const char specifier, va_list *list)
{
	if (specifier == 'c')
		return (ft_putchar(va_arg(*list, int)));
	else if (specifier == 's')
		return (ft_putstr(va_arg(*list, char *)));
	else if (specifier == 'p')
		return (ft_putptr(va_arg(*list, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(*list, int)));
	else if (specifier == 'u')
		return (ft_putnbr_unsigned(va_arg(*list, unsigned int)));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_print_hex(va_arg(*list, unsigned int), specifier));
	else if (specifier == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	size_t	i;
	int		len;

	if (!format)
		return (-1);
	va_start(list, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			i++;
			len += ft_handle_specifier(format[i], &list);
		}
		else
		{
			len += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(list);
	return (len);
}
