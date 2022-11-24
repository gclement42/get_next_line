/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:28:52 by gclement          #+#    #+#             */
/*   Updated: 2022/11/23 16:35:03 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memchr(const void *memBlock, int srchChar, size_t size)
{
	char	*str;
	size_t	i;

	str = ((char *)memBlock);
	i = 0;
	if (size <= 0)
		return (NULL);
	while (i < size)
	{
		if (((char)srchChar) == str[i])
			return (&str[i]);
		i++;
	}
	return (0);
}

void	ft_bzero(void *pointer, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)pointer)[i] = '\0';
		i++;
	}
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	x;
	size_t	dest_l;
	size_t	src_l;

	if (dest == NULL && size == 0)
		return (0);
	dest_l = ft_strlen(dest);
	src_l = ft_strlen(src);
	x = 0;
	i = dest_l;
	if (size <= dest_l)
		return (src_l + size);
	if (size > 0)
	{
		while (src[x] && (x < size - dest_l - 1))
		{
			dest[i] = src[x];
			i++;
			x++;
		}
		dest[i] = '\0';
	}
	return (dest_l + src_l);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			if (i < size - 1)
			dest[i] = src[i];
		i++;
		}
	dest[i] = '\0';
		return (ft_strlen(src));
	}
	else
		return (ft_strlen(src));
}