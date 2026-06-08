/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:31:58 by fmanno            #+#    #+#             */
/*   Updated: 2025/01/05 11:32:00 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_ptr(void *ptr, int *count)
{
	unsigned long	nbr;

	if (!ptr)
		return (ft_print_str("(nil)", count));
	nbr = (unsigned long) ptr;
	ft_print_str("0x", count);
	ft_print_nbr_base(nbr, "0123456789abcdef", count);
}
