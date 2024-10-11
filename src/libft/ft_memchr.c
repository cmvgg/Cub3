
#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	size_t			count;

	count = 0;
	temp = (unsigned char *)s;
	while (count < n)
	{
		if (temp[count] == (unsigned char)c)
			return (temp + count);
		count++;
	}
	return (0);
}
