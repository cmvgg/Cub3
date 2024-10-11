
#include "../../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	size_t			count;

	count = 0;
	temp = (unsigned char *)b;
	while (count < len)
	{
		temp[count] = (unsigned char)c;
		count++;
	}
	return (b);
}
