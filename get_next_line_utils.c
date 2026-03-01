#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substring = malloc(1);
		if (!substring)
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	if (len > s_len - start)
		len = s_len - start;
	substring = malloc(len + 1);
	if (!substring)
		return (NULL);
	ft_memcpy(substring, s + start, len);
	substring[len] = '\0';
	return (substring);
}

char	*ft_strdup(const char *s)
{
	char	*dupl;
	size_t	i;

	i = 0;
	dupl = malloc(ft_strlen(s) + 1);
	if (!dupl)
		return (NULL);
	while (i < ft_strlen(s))
	{
		dupl[i] = s[i];
		i++;
	}
	dupl[i] = '\0';
	return (dupl);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*str;
	const unsigned char	*src_1;
	size_t				i;

	str = (unsigned char *)dest;
	src_1 = (unsigned const char *)src;
	i = 0;
	while (i < n)
	{
		str[i] = src_1[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_memchr_int(const void *s, int c, size_t n)
{
	int				i;
	const unsigned char	*str;

	i = 0;
	str = (const unsigned char *)s;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	size_t strlen_s1;
	size_t strlen_s2;

	if (!s1 || !s2)
		return (NULL);
	strlen_s1 = ft_strlen(s1);
	strlen_s2 = ft_strlen(s2);
	buffer = malloc(strlen_s1 + strlen_s2 + 1);
	if (!buffer)
		return (NULL);
	buffer[strlen_s1 + strlen_s2] = '\0';
	ft_memcpy(buffer, s1, strlen_s1);
	ft_memcpy(&buffer[strlen_s1], s2, strlen_s2);
	return (buffer);
}
