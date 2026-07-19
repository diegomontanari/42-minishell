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
