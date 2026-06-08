/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:49:25 by fmanno            #+#    #+#             */
/*   Updated: 2026/01/01 18:19:47 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (!*to_find)
		return (str);
	while (*str)
	{
		i = 0;
		while (to_find[i] && str[i] && str[i] == to_find[i])
		{
			i++;
		}
		if (!to_find[i])
			return (str);
		str++;
	}
	return (0);
}
