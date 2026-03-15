#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int ft_memchr_index(char *s, char separator);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
