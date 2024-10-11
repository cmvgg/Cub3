
#include "../../includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	count;

	if (!s)
		return ;
	count = 0;
	while (s[count])
	{
		write(fd, &s[count], 1);
		count++;
	}
}
