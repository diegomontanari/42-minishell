/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:50:23 by pscarcin          #+#    #+#             */
/*   Updated: 2026/01/29 03:06:56 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned int num, const char specifier)
{
	char	*hex_digits;
	int		len;

	len = 0;
	if (specifier == 'x')
	{
		hex_digits = "0123456789abcdef";
	}
	else
	{
		hex_digits = "0123456789ABCDEF";
	}
	if (num >= 16)
		len += ft_print_hex((num / 16), specifier);
	len += ft_putchar(hex_digits[num % 16]);
	return (len);
}

static int	ft_print_pointer(unsigned long ptr)
{
	char	*hex_digits;
	int		len;

	hex_digits = "0123456789abcdef";
	len = 0;
	if (ptr >= 16)
		len += ft_print_pointer(ptr / 16);
	len += ft_putchar(hex_digits[ptr % 16]);
	return (len);
}

int	ft_putptr(void *pointer)
{
	unsigned long	ptr;
	int				len;

	ptr = (unsigned long)pointer;
	len = 0;
	if (ptr == 0)
	{
		len += ft_putstr("(nil)");
		return (len);
	}
	len += ft_putstr("0x");
	len += ft_print_pointer(ptr);
	return (len);
}
