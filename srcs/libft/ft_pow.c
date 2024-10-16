#include "../../includes/libft.h"

int	ft_pow(int n, int pot)
{
	if (pot == 0)
		return (1);
	else if (pot == 1)
		return (n);
	else if (pot < 0)
		return (-1);
	else
		return (n * ft_pow(n, --pot));
}
