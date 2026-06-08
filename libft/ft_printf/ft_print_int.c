/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:31:21 by fmanno            #+#    #+#             */
/*   Updated: 2025/02/06 17:29:38 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_int(int nbr, int *count)
{
	long	n;

	n = nbr;
	if (nbr == -2147483648)
	{
		ft_print_str("-2147483648", count);
		return ;
	}
	if (nbr < 0)
	{
		n = -nbr;
		ft_print_char('-', count);
	}
	ft_print_nbr_base((unsigned long)n, "0123456789", count);
}

void	ft_print_uns_int(unsigned int nbr, int *count)
{
	unsigned long	n;

	n = nbr;
	ft_print_nbr_base(n, "0123456789", count);
}
