#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3
#endif

#include "get_next_line.h"

int ft_memchr_index(char *s, char separator);
ssize_t read_file(char **saved, char **stash, int fd);
char *split_and_return(char **saved, char *stash, ssize_t read_bytes);
char    *extract(char *stash, char separator, int extract_return);

char    *get_next_line(int fd)
{
    static char *saved = NULL;
    char *stash;
    char *line;
    ssize_t read_bytes;

    stash = malloc(BUFFER_SIZE + 1);
    read_bytes = 1;
    if (!saved || ft_memchr_index(saved, '\n') == -1)
        read_bytes = read_file(&saved, &stash, fd);
    if (read_bytes < 0)
    {
        free(stash);
        return (NULL);
    }
    if (read_bytes == 0)
    {
        line = saved;
        saved = NULL;
    }
    else
        line = split_and_return(&saved, stash, read_bytes);
    free(stash);
    if (line)
        return (line);
    return (NULL);
}

ssize_t read_file(char **saved, char **stash, int fd)
{
    ssize_t read_bytes;
    char *remaining;
    char    *temp;
    
    read_bytes = read(fd, *stash, BUFFER_SIZE);
    if (read_bytes <= 0)
        return (read_bytes);
    (*stash)[read_bytes] = '\0';
    if (*saved && read_bytes > 0)
    {
        temp = ft_strjoin(*saved, *stash);
        free(*saved);
        *saved = temp;
    }
    else if (!(*saved) && read_bytes > 0)
        *saved = ft_strdup(*stash);
    while (read_bytes > 0 && ft_memchr_index(*saved, '\n') == -1)
    {
        read_bytes = read(fd, *stash, BUFFER_SIZE);
        (*stash)[read_bytes] = '\0';
        temp = ft_strjoin(*saved, *stash);
        free(*saved);
        *saved = temp;
        if (read_bytes == 0)
            break;
    }
    return (read_bytes);
}

char *split_and_return(char **saved, char *stash, ssize_t read_bytes)
{
    char    *line;
    char    *remaining;

    remaining = extract(*saved, '\n', -1);
    if (remaining)
    {
        line = extract(*saved, '\n', 1);
        free(*saved);
        *saved = remaining;
        return (line);
    }
    if (*saved && *saved[0] != '\0')
    {
        line = *saved;
        *saved = NULL;
        return (line);
    }
    return (NULL);
}

char *extract(char *stash, char separator, int extract_return)
{
    int i;

    i = 0;
    if (!stash)
        return (NULL);
    while (stash[i] && stash[i] != separator)
        i++;
    if (stash[i] == separator)
    {
        if (extract_return == 1)
            return (ft_substr(stash, 0, i + 1));
        else if (extract_return == -1)
            return (ft_substr(stash, i + 1, ft_strlen(stash) - i - 1));
    }
    return  (NULL);
}

int ft_memchr_index(char *s, char separator)
{
    int i;

    i = 0;
    while (s[i] != '\0')
    {
        if (s[i] == separator)
            return (i);
        i++;
    }
    return (-1);
}

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;

    fd = open("fd.txt", O_RDONLY);
    printf("line : %s\n", get_next_line (fd));
    fd = open("fd1.txt", O_RDONLY);
    printf("line : %s\n", get_next_line (fd));
}
