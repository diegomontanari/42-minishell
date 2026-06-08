/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:31:12 by fmanno            #+#    #+#             */
/*   Updated: 2025/02/06 17:27:54 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_str(const char *s, int *count)
{
	size_t	len;

	if (!s)
		ft_print_str("(null)", count);
	else
	{
		len = ft_strlen(s);
		write(1, s, len);
		*count += len;
	}
}
