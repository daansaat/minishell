#ifndef GET_NEXT_LINE_H
 #define GET_NEXT_LINE_H
 #include <stdlib.h>
 #include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
// void	*ft_memset(void *b, int c, size_t len);
// void	*ft_calloc(size_t count, size_t size);

#endif