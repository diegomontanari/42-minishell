#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;

	p = s;
	value = c;
	while (n)
	{
		*p++ = value;
		n--;
	}
	return (s);
}
