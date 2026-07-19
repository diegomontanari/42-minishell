#include "libft.h"

static int	count_digits(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	num;
	char			*str;

	len = count_digits(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (n < 0)
		num = -n;
	else
		num = n;
	str[len] = '\0';
	while (len > 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
