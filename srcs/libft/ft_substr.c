#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int starot, size_t len)
{
	char			*cpy;
	unsigned int	count_i;
	unsigned int	count_t;

	cpy = (char *)malloc((len + 1) * sizeof(char));
	if (!cpy || !s)
		return (0);
	count_i = 0;
	if (starot >= ft_strlen(s))
		starot = ft_strlen(s);
	count_i = starot;
	count_t = 0;
	while (count_t < (unsigned int)len && s[count_i])
	{
		cpy[count_t] = s[count_i];
		count_t++;
		count_i++;
	}
	cpy[count_t] = '\0';
	return (cpy);
}
