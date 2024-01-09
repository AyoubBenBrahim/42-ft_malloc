
#include "../inc/malloc.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*tmp_src;
	char	*tmp_dst;

	tmp_src = (char *)src;
	tmp_dst = (char *)dst;
	i = 0;
	while (i < n)
	{
		*tmp_dst = *tmp_src;
		tmp_dst++;
		tmp_src++;
		i++;
	}
	return (dst);
}

/*
****
*/

void		*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*tmp = (unsigned char)c;
		tmp++;
		i++;
	}
	return (b);
}

/*
****
*/

size_t		ft_strlen(const char *s)
{
	size_t		size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

/*
****
*/

int		ft_islower(int c)
{
	if (c < 'a' || c > 'z')
		return (0);
	else
		return (1);
}

/*
****
*/

void	ft_strupper(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_islower(str[i]))
			str[i] -= 32;
		i++;
	}
}

/*
****
*/

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

/*
****
*/

int	ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
			i += ft_putchar(s[i]);
	}
	return (i);
}