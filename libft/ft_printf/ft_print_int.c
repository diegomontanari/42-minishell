#include "ft_printf.h"

void	ft_print_int(int nbr, int *count)
{
	long	n;

	n = nbr;
	if (nbr == -2147483648)
	{
		ft_print_str("-2147483648", count);
		return ;
	}
	if (nbr < 0)
	{
		n = -nbr;
		ft_print_char('-', count);
	}
	ft_print_nbr_base((unsigned long)n, "0123456789", count);
}

void	ft_print_uns_int(unsigned int nbr, int *count)
{
	unsigned long	n;

	n = nbr;
	ft_print_nbr_base(n, "0123456789", count);
}
