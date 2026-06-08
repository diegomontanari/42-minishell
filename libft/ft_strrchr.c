/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 17:17:20 by fmanno            #+#    #+#             */
/*   Updated: 2024/12/30 15:41:53 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_match;

	last_match = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			last_match = s;
		}
		s++;
	}
	if ((char)c == *s)
	{
		last_match = s;
	}
	return ((char *)last_match);
}
