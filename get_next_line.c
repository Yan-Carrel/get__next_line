#ifndef BUFFER_SIZE
#define BUFFER_SIZE 3
#endif

#include "get_next_line.h"
#include <stdio.h>

int     n_index(char *stash, char separator, size_t read_bytes);
char *extract(char *stash, char separator, int extract_return, size_t read_bytes);
char *return_line(char **saved, char *stash, size_t *read_bytes, int fd);

char    *get_next_line(int fd)
{
    static char *saved = NULL;
    char *stash;
    char *temp;
    size_t read_bytes;

    stash = malloc (BUFFER_SIZE + 1);
    read_bytes = -2;
    if (saved && ft_memchr_int(saved, '\n', ft_strlen(saved)) != -1)
        return(split_and_return(&saved));    
    while (!saved || ft_memchr_int(saved, '\n', ft_strlen(saved)) == -1)  // while no \n in stash 
    {
        read_bytes = read(fd, stash, BUFFER_SIZE);
        if (read_bytes <= 0)
            break;
        stash[read_bytes] = '\0';
        if (!(saved))
            saved = ft_strdup(stash);
        else
        {
            temp = saved;
            saved = ft_strjoin(saved, stash);
            free(temp);
            free(stash);
        }
        free(stash);
    }
    if (!saved)
        return (NULL);
    return(split_and_return(&saved));
}

char *split_and_return(char *saved)
{
    
}

// char *return_line(char **saved, char *stash, size_t *read_bytes, int fd)
// {
//     char *temp;
//     char *result;
//     char *rest_of_stash;
//     char *char_with_line;

//     if (ft_memchr_int(*saved, '\n', ft_strlen(*saved)))
//     {
//         temp = *saved;
//         saved = extract(*saved, '\n', 1, ft_strlen(*saved));
//         return (temp);
//     }
//     while (ft_memchr_int(stash, '\n', read_bytes))
//     {
//         read_bytes = read(fd, stash, BUFFER_SIZE);
//         if (read_bytes == 0)
//             break; 
//         stash[*read_bytes] = '\0';
//         *saved = ft_strjoin(*saved, stash);
//         if (ft_memchr_int(*saved, '\n', ft_strlen(*saved)))
//             break;
//     }
//     if (!(*saved))
//         return (NULL);
//     else
//         return (return_line(*saved, '\n', ft_strlen(*saved), fd));
//     return (NULL);
// }

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
