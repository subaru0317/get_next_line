/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:37:28 by smihata           #+#    #+#             */
/*   Updated: 2023/03/28 16:48:19 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 42

size_t	ft_strlen(const char *s)
{
	size_t	len;

	// original
	if (!s)
		return (0);
	len = 0;
	while (*s++ != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	void	*ptr;

	ptr = dst;
	if (dst == src)
		return (ptr);
	while (len--)
		*(unsigned char *)dst++ = *(const unsigned char *)src++;
	return (ptr);
}

char	*ft_strdup(const char *str)
{
	char	*cpy;
	size_t	len;

	len = ft_strlen(str);
	cpy = (char *)malloc(sizeof(char) * (len + 1));
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, str, len + 1);
	return (cpy);
}

char	*ft_strnjoin(char *s1, char *s2, size_t len)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (s1_len + len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcpy(dst + s1_len, s2, len + 1);
	return (dst);
}

// cが存在する場合		: cを含めた長さ
// cが存在しない場合	: strlen(s)
size_t	ft_strchr_len(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

// -1 : error
// 0  : \n は存在しない
// 1  : \n が存在する
int	find_newline(int fd, char **line, char **st_arr, char *buf)
{
	char	*tmp;
	size_t	len;
	int		value;

	value = -1;
	if (fd < 0)
		return (value);
	tmp = *line;
	len = ft_strchr_len(buf, '\n');
	*line = ft_strnjoin(tmp, buf, len);
	free(tmp);
	if (*line == NULL)
		return (value);
	free(*st_arr);
	// \nが存在する
	if (buf[len - 1] == '\n')
	{
		// buf + len + 1がbuffer overrunをするので len == 1の時は特別扱い。
		if (len == 1)
		{
			*st_arr = NULL;
		}
		else
		{
			// *st_arr = ft_strdup(buf + len + 1);
			*st_arr = ft_strdup(buf + len);
		}
		if (*st_arr == NULL)
			value = 1;
	}
	// \nが存在しない
	else
	{
		*st_arr = NULL;
		value = 0;
	}
	return (value);
}

void	free_all(char **line, char **st_arr)
{
	return ;
	size_t	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
	i = 0;
	while (st_arr[i])
	{
		free(st_arr[i]);
		i++;
	}
	free(st_arr);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	static char	*st_arr;
	int			len;
	int			branch;

	if (fd < 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		len = read(fd, buf, BUFFER_SIZE);
		// read error
		if (len < 0)
		{
			free_all(&line, &st_arr);
			break ;
		}
		buf[len] = '\0';
		if (len == 0 && st_arr == NULL)
		{
			// free(line);
			// line = ft_strdup("\n");
			break ;
		}
		// st_arrにまだ文字列が残っている間は処理を行う
		// if (len == 0 && st_arr[0] != '\0')
		// {
			
		// }
		branch = find_newline(fd, &line, &st_arr, buf);
		// \n が存在する
		if (branch == 1)
		{
			break ;
		}
		if (branch == -1)
		{
			free_all(&line, &st_arr);
			break ;
		}
	}
	return (line);
}


// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (1);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	fd1 = open("test.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}

// __attribute__((destructor))
// static void destructor(void){
//     system("leaks -q a.out");
// }