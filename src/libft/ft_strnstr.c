
#include "../../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	count;
	size_t	count_t;
	size_t	search;

	count = 0;
	count_t = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (count < len && haystack[count])
	{
		if (haystack[count] == needle[count_t])
		{
			search = count;
			while (search < len && haystack[search] == needle[count_t])
			{
				search++;
				count_t++;
				if (needle[count_t] == '\0')
					return ((char *)haystack + count);
			}
			count_t = 0;
		}
		count++;
	}
	return (0);
}
