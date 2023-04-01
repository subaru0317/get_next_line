/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:07:36 by smihata           #+#    #+#             */
/*   Updated: 2023/04/01 13:03:11 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_all(char **line, char **st_arr)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		line[i] = NULL;
		i++;
	}
	i = 0;
	while (st_arr[i])
	{
		free(st_arr[i]);
		st_arr[i] = NULL;
		i++;
	}
	line = NULL;
	st_arr = NULL;
}

int	ft_connect_line_to_save(char **line, char **save)
{
	size_t	len_to_nl;
	char	*tmp;
	int		line_have_nl;

	len_to_nl = ft_strchr_len(*save, '\n');
	if (len_to_nl >= 1 && save[0][len_to_nl - 1] == '\n')
	{
		tmp = *line;
		*line = ft_strnjoin(tmp, *save, len_to_nl);
		free(tmp);
		tmp = *save;
		*save = ft_strdup(tmp + len_to_nl);
		free(tmp);
		tmp = NULL;
		line_have_nl = 1;
	}
	else
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
		line_have_nl = 0;
	}
	return (line_have_nl);
}

int	ft_eof_or_read_error(int read_buf_size, char **line)
{
	if (read_buf_size == 0)
	{
		if (ft_strlen(*line) == 0)
		{
			free(*line);
			*line = NULL;
		}
		return (0);
	}
	else
		return (1);
}

int	ft_get_new_line(int fd, char **line, char **save)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp_line;
	int		read_buf_size;
	int		len_to_nl;

	while (1)
	{
		read_buf_size = read(fd, buf, BUFFER_SIZE);
		if (read_buf_size <= 0)
			return (ft_eof_or_read_error(read_buf_size, line));
		buf[read_buf_size] = '\0';
		len_to_nl = ft_strchr_len(buf, '\n');
		tmp_line = *line;
		*line = ft_strnjoin(tmp_line, buf, len_to_nl);
		free(tmp_line);
		tmp_line = NULL;
		if (line[0][ft_strlen(*line) - 1] == '\n')
		{
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
