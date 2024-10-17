#include "../../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			count;

	if (dst == NULL && src == NULL)
		return (NULL);
	count = 0;
	if (dst <= src)
	{
		while (count < len)
		{
			(((unsigned char *)dst)[count] = ((unsigned char *)src)[count]);
			count++;
		}
	}
	else
	{
		while (len > 0)
		{
			(((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1]);
			len--;
		}
	}
	return (dst);
}