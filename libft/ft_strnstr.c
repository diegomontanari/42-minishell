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
