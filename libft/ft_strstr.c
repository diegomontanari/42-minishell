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
