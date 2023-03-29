/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:36 by smihata           #+#    #+#             */
/*   Updated: 2023/03/29 19:45:43 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// #define BUFFER_SIZE 42

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
	line = NULL;
	st_arr = NULL;
}

// *line == NULL なので free はいらない ???
int	ft_connect_line_to_save(char **line, char **save)
{
	size_t	len_to_nl;
	char	*tmp_line;
	char	*tmp_save;
	int		line_have_nl;

	len_to_nl = ft_strchr_len(*save, '\n');
	// 1. save内に\nが存在する場合
	if (save[0][len_to_nl - 1] == '\n')
	{
		// save = "s1\ns2"
		// line <- "s1\n"
		// save <- "s2"
		tmp_line = *line;
		*line = ft_strnjoin(tmp_line, *save, len_to_nl);
		free(tmp_line);
		tmp_save = *save;
		*save = ft_strdup(tmp_save + len_to_nl);
		free(tmp_save);
		line_have_nl = 1;
	}
	// 2. save内に\nが存在しない場合
	else
	{
		// save = "s";
		// line <- "s";
		// save = NULL;
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
		line_have_nl = 0;
	}
	return (line_have_nl);
}

// saveはNULLが含まれているはず
int	ft_get_new_line(int fd, char **line, char **save)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp_line;
	int		read_buf_size;
	int		len_to_nl;

	while (1)
	{
		read_buf_size = read(fd, buf, BUFFER_SIZE);
		if (read_buf_size < 0)
			return (1);
		if (read_buf_size == 0) // EOFに到達した
			return (0);
		buf[read_buf_size] = '\0';
		len_to_nl = ft_strchr_len(buf, '\n');
		tmp_line = *line;
		*line = ft_strnjoin(tmp_line, buf, len_to_nl);
		free(tmp_line);
		if (line[0][ft_strlen(*line) - 1] == '\n') // \nに到達した
		{
			// buf = "s1\ns2"
			// line <- "s1\n"
			// save <- "s2"
			if (ft_strlen(buf) == 1)
				*save = NULL;
			else
				*save = ft_strdup(buf + len_to_nl);
			return (0);
		}
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	int			line_have_nl;
	int			error;

	// save = malloc(4);
	// save[0] = 'a'; save[1] = 'c'; save[2] = 'b'; save[3] = '\0';
	if (fd < 0)
		return (NULL);
	line = NULL;
	if (save)
	{
		line_have_nl = ft_connect_line_to_save(&line, &save);
		if (line_have_nl)
			return (line);
	}
	error = ft_get_new_line(fd, &line, &save);
	if (error)
		free_all(&line, &save);
	return (line);
}


// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	fd1 = open("test.txt", O_RDONLY);
// 	i = 1;
// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }

// __attribute__((destructor))
// static void destructor(void){
//     system("leaks -q a.out");
// }