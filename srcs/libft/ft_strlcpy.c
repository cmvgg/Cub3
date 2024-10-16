#include "../../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	count;
	unsigned int	output;

	if (!dst && !src)
		return (0);
	output = 0;
	while (src[output] != '\0')
		output++;
	if (dstsize == 0)
		return (output);
	count = 0;
	while (src[count] != '\0' && count < (dstsize - 1))
	{
		dst[count] = src[count];
		count++;
	}
	dst[count++] = '\0';
	return (output);
}
