/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscarcin <pscarcin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:50:36 by pscarcin          #+#    #+#             */
/*   Updated: 2026/01/29 03:06:07 by pscarcin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
	{
		len += ft_putstr("(null)");
		return (len);
	}
	while (str[len])
	{
		write(1, &(str[len]), 1);
		len++;
	}
	return (len);
}

int	ft_putnbr(int nbr)
{
	int	len;

	len = 0;
	if (nbr == -2147483648)
		return (ft_putstr("-2147483648"));
	if (nbr < 0)
	{
		len += ft_putchar('-');
		nbr *= -1;
		len += ft_putnbr(nbr);
		return (len);
	}
	if (nbr >= 10)
	{
		len += ft_putnbr(nbr / 10);
		len += ft_putnbr(nbr % 10);
		return (len);
	}
	len += ft_putchar(nbr + '0');
	return (len);
}

int	ft_putnbr_unsigned(unsigned int nbr)
{
	int	len;

	len = 0;
	if (nbr >= 10)
	{
		len += ft_putnbr_unsigned(nbr / 10);
		len += ft_putnbr_unsigned(nbr % 10);
		return (len);
	}
	else
	{
		len += ft_putchar(nbr + '0');
		return (len);
	}
}
