#include "libft.h"
#include "exec.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

char    *get_next_path(char *path_env, char *cmd, int i, int j)
{
		char    *path;

		path = malloc(sizeof(char) * (i - j + ft_strlen(cmd) + 2));
		if (!path) {
			perror("malloc()");
			exit(EXIT_FAILURE);
		}
		ft_strlcpy(path, &path_env[j], i - j + 1);
		ft_strlcpy(&path[i - j], "/", 2);
		ft_strlcpy(&path[i - j + 1], cmd, ft_strlen(cmd) + 1);
		return (path);
}

char    *search_path(char *cmd)
{
	struct stat sb;
	char        *path_env;
	char        *path;
	int         i;
	int         j;
	
	i = 0;
	path_env = getenv("PATH");
	while (path_env[i])
	{
		j = i;
		while (path_env[i] && path_env[i] != ':')
			i++;
		path = get_next_path(path_env, cmd, i, j);
		if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR) // still check if executable or not??
			return (path);
		else
			free(path);
		if (path_env[i] == ':')
			i++;
	}
	// errno = ENOENT;//127; // still error handling!
	return (NULL);
}

