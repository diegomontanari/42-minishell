/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr_base                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:31:49 by fmanno            #+#    #+#             */
/*   Updated: 2025/01/05 11:31:50 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_nbr_base(unsigned long nbr, char *base, int *count)
{
	size_t	len;

	len = ft_strlen(base);
	if (nbr == 0)
	{
		ft_print_char(base[0], count);
		return ;
	}
	if (nbr >= len)
	{
		ft_print_nbr_base(nbr / len, base, count);
	}
	ft_print_char(base[nbr % len], count);
}
