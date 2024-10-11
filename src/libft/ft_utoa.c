
#include "../../includes/libft.h"

static unsigned int	ft_len_num(unsigned int n)
{
	unsigned int	count;

	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*ft_str_num(char *str, unsigned int n, unsigned int len)
{
	unsigned int	mod;

	str[len] = '\0';
	len--;
	while (len > 1)
	{
		mod = (n % 10);
		str[len] = mod + '0';
		n /= 10;
		len--;
	}
	str[len] = (n % 10) + '0';
	str[0] = (n / 10) + '0';
	return (str);
}

char	*ft_utoa(unsigned int n)
{
	char			*result;
	unsigned int	len_num;

	len_num = ft_len_num(n);
	result = (char *)malloc((len_num + 1) * sizeof(char));
	if (!result)
		return (0);
	if (n < 10)
	{
		result[0] = n + '0';
		result[1] = '\0';
	}
	else
		result = ft_str_num(result, n, len_num);
	return (result);
}
