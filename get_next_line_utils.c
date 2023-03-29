/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smihata <smihata@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:37:11 by smihata           #+#    #+#             */
/*   Updated: 2023/03/29 19:29:49 by smihata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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