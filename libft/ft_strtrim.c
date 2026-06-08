/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanno <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:00:45 by fmanno            #+#    #+#             */
/*   Updated: 2024/12/30 17:36:34 by fmanno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	if (!s1 || !set || s1[0] == '\0')
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, (int)s1[start]))
		start++;
	while (end > start && ft_strrchr(set, (int)s1[end]))
		end--;
	if (end < start)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}
