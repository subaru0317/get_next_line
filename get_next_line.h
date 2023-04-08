/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:36:39 by smihata           #+#    #+#             */
/*   Updated: 2023/04/08 09:55:23 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strnjoin(char *s1, char *s2, size_t len);
char	*ft_strdup(const char *str);
size_t	ft_strchr_len(char *s, char c);
char	*free_all(char **line, char **save);

char	*get_next_line(int fd);
#endif