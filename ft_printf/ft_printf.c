#include <unistd.h>
#include <stdarg.h>

int	ft_putchar(char c)
{
	return (write (1, &c, 1));
}

int	hexdecimal(unsigned long long n)
{
	char				*base;
	unsigned long long	counter;

	base = "0123456789abcdef";
	counter = 0;
	if (n >= 16)
		counter += hexdecimal (n / 16);
	counter += ft_putchar (base[n % 16]);
	return (counter);
}

int	ft_putnbr(long long n)
{
	int	counter;
	int	isneg;

	counter = 0;
	isneg = 0;
	if (n == -2147483648)
	{
		counter += ft_putchar ('-') + ft_putchar ('2');
		n = 147483648;
	}
	if (n < 0)
	{
		counter += ft_putchar ('-');
		n = n * -1;
		isneg = 1;
	}
	if (n < 10)
	{
		n = n + 48;
		counter += ft_putchar(n);
		return (1 + isneg);
	}
	counter += ft_putnbr (n / 10);
	counter += ft_putnbr (n % 10);
	return (counter);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	return (i);
}

int	identifier(char c, va_list arg)
{
	int	next = 0;

	 if (c == 's')
		next += ft_putstr (va_arg(arg, char *));
	else if (c == 'd')
		next += ft_putnbr(va_arg(arg, int));
	else if (c == 'x')
		next += hexdecimal(va_arg(arg, unsigned int));
	return(next);
}

int ft_printf(const char *c, ...)
{
	int		count;
	va_list	arg;

	va_start(arg, c);
	count = 0;
	while (*c)
	{
		if (*c == '%')
		{
			count += identifier(*(++c), arg);
		}
		else
			count += ft_putchar(*c);
		c++;
	}
	va_end(arg);
	return (count);
}

// int main()
// {
// 	ft_printf("this is number %d,\n this is string %s, \n this is hex %x", 55, "hla", 54);
// }