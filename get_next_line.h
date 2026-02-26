#if !defined(GET_NEXT_LINE_H)
#define GET_NEXT_LINE_H

#define BUFFER_SIZE 3
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
