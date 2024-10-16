#include "../../includes/libft.h"

static int	pf_pct(va_list *ap, int ct, const char *format, int **result)
{
	char	*width;

	ct++;
	ct = pf_man_fmt(ap, ct, format, &width);
	if (format[ct] == 'c')
		pf_find_char(ap, &width, result);
	else if (format[ct] == '%')
		pf_find_pct(&width, result);
	else if (format[ct] == 's')
		pf_find_str(ap, &width, result);
	else if (format[ct] == 'd' || format[ct] == 'i')
		pf_find_int(ap, &width, result);
	else if (format[ct] == 'u')
		pf_find_uns(ap, &width, result);
	else if (format[ct] == 'x' || format[ct] == 'X')
		pf_find_hex(ap, format[ct], &width, result);
	else if (format[ct] == 'p')
		find_ptr(ap, &width, result);
	free(width);
	return (ct + 1);
}

int	printf(const char *format, ...)
{
	va_list	ap;
	int		*result;
	int		ct;

	va_starot(ap, format);
	result = (int *)malloc(sizeof(int) * 1);
	(*result) = 0;
	ct = 0;
	while (format[ct])
	{
		if (format[ct] == '%')
			ct = pf_pct(&ap, ct, format, &result);
		else
		{
			ft_putchar_fd(format[ct], 1);
			(*result) += 1;
			ct++;
		}
	}
	ct = *result;
	free(result);
	va_end(ap);
	return (ct);
}
