	#include "get_next_line.h"

char	*ft_getline(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_newsave(char *save)
{
	char	*newsave;
	int		i;
	int		j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return ("");
	newsave = malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	i++;
	j = 0;
	while (save[i])
	{
		newsave[j] = save[i];
		j++;
		i++;
	}
	newsave[j] = '\0';
	free(save);
	return (newsave);
	
}

char	*get_next_line(int fd)
{
    static char *save = "";
    char        buff[BUFFER_SIZE + 1];
	char		*line;
    int         b_read;

    b_read = 1;
    while (!ft_strrchr(save, '\n') && b_read != 0)
    {
    	b_read = read(fd, buff, BUFFER_SIZE);
		// if (b_read == 0)
		// 	return (NULL);
    	buff[b_read] = '\0';
		save = ft_strjoin(save, buff);
    }
	line = ft_getline(save);
    save = ft_newsave(save);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
    return (line);
}
