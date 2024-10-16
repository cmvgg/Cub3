#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			amt;
	size_t			i;

	amt = count * size;
	ptr = malloc(amt);
	if (!ptr)
		return (0);
	i = 0;
	while (i < amt)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
