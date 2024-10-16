#include "../../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	int		count;
	char	*str;

	count = ft_strlen(s1);
	str = (char *)malloc((count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	count = 0;
	while (s1[count])
	{
		str[count] = s1[count];
		count++;
	}
	str[count] = '\0';
	return (str);
}
