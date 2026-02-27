#include "get_next_line.h"
#include <stdio.h>

static char *saved = NULL;
static int found_n = 0;
static int cond_3 = 0;
// char *save_subs(char *saved, char *stash);
int     n_index(char *stash, char separator);
char *concat_chars(char *saved, char *stash);
char *extract_return(char *stash, char separator);
char    *extract_remaining(char *stash, char separator);
char    *get_next_line(int fd)
{
    char *stash;
    char separator;
    char *temp;
    char *char_return;
    int index;
    size_t read_bytes;
    // int found_n;
    // int cond_3;
    
    // cond_3 = 0;
    separator = '\n';
    stash = malloc (BUFFER_SIZE + 1);
    read_bytes = -2;
    while (read_bytes != 0 && read_bytes != -1 && !(found_n))
    {
        if (found_n == 1)
        {
            free(saved);
            saved = NULL;
            printf("%s", "freeing");
        }
        read_bytes = read(fd, stash, BUFFER_SIZE);
        // printf("saved +: %s", saved);
        index = n_index(stash, separator);
        found_n = 0;
        stash[BUFFER_SIZE] = '\0';
        if (cond_3)
        {
            saved = extract_remaining(stash, separator);
            cond_3 = 0;
        }
        printf("index : %d\n", index);
        if (index == -1)
        {
            saved = concat_chars(saved, stash);
            printf("condition 1 : saved : %s\n", saved);
        }
        else if (index == BUFFER_SIZE - 1)
        {
            saved = concat_chars(saved, stash);
            printf("condition 2 : saved + stash : %s\n", saved);
            found_n = 1;
            return (saved);
        }
        else if (index > -1 && index < (BUFFER_SIZE - 1))
        {
            char_return = extract_return(stash, separator);
            cond_3 = 1;
            // found_n = 1;
            if (saved)
            {
                // free(saved);
                // saved = extract_remaining(stash, separator);
                printf("conditions 3 saved : %s\n" ,saved);
                return (concat_chars(saved, char_return));
            }
            else
                return (stash);
        }
    }
}

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
        return (ft_substr(stash, 0, ft_strlen(stash)));
    }
    stash_len = ft_strlen(stash);
    result = malloc(saved_len + stash_len + 1);
    ft_memcpy(result, temp, saved_len);
    ft_memcpy(&result[saved_len], stash, stash_len);
    result[saved_len + stash_len] = '\0';
    // free(saved);
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
    printf("line : %s", get_next_line (fd));
    printf("line : %s", get_next_line (fd));
    // printf("line : %s", get_next_line (fd));
    // printf("line : %s", get_next_line (fd));
//     // char *saved = NULL;

    // char *saved = "ABC"; 
    // char *stash = "DE\n";
    // printf("result : %s\n", concat_chars(saved, stash));
    // ("empty saved : %s\n", save_subs(saved, "ab\n"));
}
