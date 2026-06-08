/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:03:25 by fmanno            #+#    #+#             */
/*   Updated: 2024/12/30 17:32:53 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if (*str2 == '\0')
		return ((char *)str1);
	while (*str1 && n > 0)
	{
		i = 0;
		while (str1[i] == str2[i] && str2[i] && i < n)
		{
			i++;
		}
		if (str2[i] == '\0')
			return ((char *)str1);
		str1++;
		n--;
	}
	return (NULL);
}
