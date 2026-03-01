#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3
#endif

#include "get_next_line.h"
#include <stdio.h>

int     n_index(char *stash, char separator);
char *extract(char *stash, char separator, int extract_return, size_t read_bytes);
char *return_line(char **saved, char *stash, size_t *read_bytes, int index, int fd);

char    *get_next_line(int fd)
{
    static char *saved = NULL;
    char *stash;
    int index;
    size_t read_bytes;

    stash = malloc (BUFFER_SIZE + 1);
    read_bytes = -2;
    while (read_bytes != 0 && read_bytes != -1)
    {
        read_bytes = read(fd, stash, BUFFER_SIZE);
        if (read_bytes == -1 || !stash)
            return (NULL);
        stash[read_bytes] = '\0';
        index = n_index(stash, '\n');
        if (index == -1)
        {
            if (!(saved))
                saved = ft_strdup("");
            saved = ft_strjoin(saved, stash);
        }
        else
            return(return_line(&saved, stash, &read_bytes, index, fd));
    }
    if (saved)
        return (return_line(&saved, stash, &read_bytes, index, fd));
    free(saved);
    free(stash);
    return (NULL);
}

char *return_line(char **saved, char *stash, size_t *read_bytes, int index, int fd)
{
    char *temp;

    if (*read_bytes == 0)
    {
        if (*saved && (*saved)[0] != '\0')
        {
            index = n_index(*saved, '\n');
            if (index > -1)
            {
                temp = extract(stash, '\n', 1, *read_bytes);
                *saved = extract(stash, '\n', 0, *read_bytes);
                return (temp);
            }
            temp = *saved;
            *saved = NULL;
            return (temp);
        }
        return (NULL);
    }
    if (index == *read_bytes - 1)
    {
        if (!(*saved))
            *saved = ft_strdup("");
        temp = ft_strjoin(*saved, stash);
        *saved = NULL;
        return (temp);
    }
    else if (index > -1 && index < (*read_bytes - 1))
    {
        if (!(*saved))
        {
            *saved = extract(stash, '\n', 0, *read_bytes);
            return (extract(stash, '\n', 1, *read_bytes));
        }
        else
        {
            temp = *saved;
            *saved = extract(stash, '\n', 0, *read_bytes);
            return(ft_strjoin(temp, extract(stash, '\n', 1, *read_bytes)));
        }
    }
    return (NULL);
}

char *extract(char *stash, char separator, int extract_return, size_t read_bytes)
{
    int i;

    i = 0;
    if (!stash)
    return (NULL);
    while (i < read_bytes && stash[i] != separator)
        i++;
    if (stash[i] == separator)
    {
        if (extract_return)
            return (ft_substr(stash, 0, i + 1));
        else
            return (ft_substr(stash, i + 1, read_bytes - i + 1));
    }
    return  (NULL);
}


int n_index(char *stash, char separator)
{
    int i;

    i = 0;
    while (i < BUFFER_SIZE && stash[i] && stash[i] != separator)
        i++;
    if (stash [i] == separator)
        return (i);
    return (-1);
}

#include <fcntl.h>

int main(void)
{
    int fd;

    fd = open("fd.txt", O_RDONLY);
    printf("line : %s\n", get_next_line (fd));
    printf("line : %s\n", get_next_line (fd));
    printf("line : %s\n", get_next_line (fd));
    printf("line : %s\n", get_next_line (fd));
    printf("line : %s\n", get_next_line (fd));
}
