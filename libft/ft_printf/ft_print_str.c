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
