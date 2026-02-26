#include "get_next_line.h"
#include <stdio.h>

static char *saved = NULL;
// char *save_subs(char *saved, char *stash);
int     n_index(char *stash, char separator);
char *concat_chars(char *saved, char *stash);
char *extract_return(char *stash, char separator);
char    *extract_remaining(char *stash, char separator);
char    *get_next_line(int fd)
{
    char *stash;
    char separator;
    int index;
    char *temp;
    char *char_return;
    
    separator = '\n';
    stash = malloc (BUFFER_SIZE);
    while (read(fd, stash, BUFFER_SIZE) != 0)
    {
        stash[BUFFER_SIZE] = '\0';
        if (n_index(stash, separator) == -1)
            saved = concat_chars(saved, stash);
        else if (n_index(stash, separator) == BUFFER_SIZE - 1)
            return (concat_chars(saved, stash));
        else if (n_index(stash, separator) > -1 && n_index(stash, separator) < (BUFFER_SIZE - 1))
        {
            char_return = extract_return(stash, separator);
            if (saved)
            {
                temp = saved;
                temp = malloc (ft_strlen(temp + ft_strlen(char_return)) + 1);
                ft_memcpy(temp, temp, ft_strlen(temp));
                ft_memcpy(&temp[ft_strlen(temp)], char_return, ft_strlen(char_return));
                free(saved);
                saved = concat_chars(saved, extract_remaining(stash, separator));
                printf("saved : %s\n" ,saved);
                return (saved);
            }
            else
                return (stash);
        }
    }
}

// char *save_subs(char *saved, char *stash)
// {
//     size_t save_len;
//     size_t stash_len;
//     char *temp;

//     save_len = 0;
//     stash_len = 0;
//     temp = NULL;
//     if (saved)
//     {
//         save_len = ft_strlen(saved);
//         temp = saved;
//     }
//     stash_len = ft_strlen(stash);
//     saved = malloc(save_len + stash_len);
//     if (!saved)
//         return (NULL) ;
//     ft_memcpy(saved, temp, save_len);
//     ft_memcpy(&saved[save_len], stash, stash_len);
//     free(saved);
//     return (saved);
// }

char *concat_chars(char *saved, char *stash)
{
    size_t saved_len;
    size_t stash_len;
    char *result;
    char *temp;

    saved_len = 0;
    temp = NULL;
    if (saved)
    {
        temp = saved;
        saved_len = ft_strlen(temp);
    }
    else
    {
        if (!stash)
            return (NULL);
        return (stash);
    }
    stash_len = ft_strlen(stash);
    result = malloc(saved_len + stash_len + 1);
    ft_memcpy(result, temp, saved_len);
    ft_memcpy(&result[saved_len], stash, stash_len);
    result[saved_len + stash_len] = '\0';
    free(saved);
    return (result);
}

char *extract_return(char *stash, char separator)
{
    int i;
    
    i = 0;
    if (!stash)
        return (NULL);
    while (i < BUFFER_SIZE && stash[i] != separator)
        i++;
    if (stash[i] == separator)
        return (ft_substr(stash, 0, i + 1));
    return  (NULL);
}

char    *extract_remaining(char *stash, char separator)
{
    int i;
    
    i = 0;
    if (!stash)
        return (NULL);
    while (i < BUFFER_SIZE && stash[i] != separator)
        i++;
    if (stash[i] == separator)
        return (ft_substr(stash, i + 1, BUFFER_SIZE - i + 1));
    return  (NULL);
}


int n_index(char *stash, char separator)
{
    int i;

    i = 0;
    while (stash[i] != separator && i < BUFFER_SIZE)
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
    printf("line : %s", get_next_line (fd));
    // printf("line : %s", get_next_line (fd));
    // printf("line : %s", get_next_line (fd));
//     // char *saved = NULL;

    // char *saved = "ABC"; 
    // char *stash = "DE\n";
    // printf("result : %s\n", save_subs(saved, stash));
    // ("empty saved : %s\n", save_subs(saved, "ab\n"));
}
