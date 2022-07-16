#include "exec.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

// char    *get_next_path()
// {
    
// }

char    *search_path(char *cmd)
{
    struct stat sb;
    char        *path_env;
    char        *path;
    int         i;
    int         j;
    
    i = 0;
    path_env = getenv("PATH");
    path = path_env;
    while (path_env[i])
    {
        j = i;
        while (path_env[i] && path_env[i] != ':')
            i++;
        path = malloc(sizeof(char) * (i - j + ft_strlen(cmd) + 2));
        if (!path) {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }
        ft_strlcpy(path, &path_env[j], i - j + 1);
        ft_strlcpy(&path[i - j], "/", 2);
        ft_strlcpy(&path[i - j + 1], cmd, ft_strlen(cmd) + 1);
        if (stat(path, &sb) == 0) // still check if executable or not??
            return (path);
        else
            free(path);
        if (path_env[i] == ':')
            i++;
    }
    errno = 127;
    return (NULL);
}
