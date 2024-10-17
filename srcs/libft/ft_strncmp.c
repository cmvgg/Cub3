#include "../../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_t;
	unsigned char	*s2_t;
	size_t			count;

	count = 0;
	s1_t = (unsigned char *)s1;
	s2_t = (unsigned char *)s2;
	while (count < n && s1_t[count] && s2_t[count])
	{
		if (s1_t[count] != s2_t[count])
			return (s1_t[count] - s2_t[count]);
		count++;
	}
	if (count < n)
		return (s1_t[count] - s2_t[count]);
	return (0);
}