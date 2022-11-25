/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:28:29 by gclement          #+#    #+#             */
/*   Updated: 2022/11/25 17:51:13 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

void	*ft_calloc( size_t count, size_t size)
{
	void	*ptr;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	if (!(s1 == NULL || s2 == NULL))
	{	
		dest = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1),
				sizeof(char));
		if (!dest)
			return (NULL);
		ft_strlcpy(dest, ((char *)s1), (ft_strlen(s1) + 1));
		ft_strlcat(dest, s2, (ft_strlen(s1) + (ft_strlen(s2) + 1)));
		return (dest);
	}
	return (NULL);
}

char	*allocate_and_read(char *dest, int fd, int size)
{
	char	*str;
	char	*tmp;

	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	read(fd, str, size);
	str[size] = '\0';
	tmp = ft_strjoin(dest, str);
	return (tmp);
}

char	*search_line(char *str, int fd, int *size)
{
	while (ft_memchr(str, '\n', *size) == 0 && ft_memchr(str, '\0', *size) != 0)
	{
		*size += BUFFER_SIZE;
		str = allocate_and_read(str, fd, *size);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*tmp;
	int			size;
	static char	*overflow;

	size = BUFFER_SIZE;
	str = NULL;
	if (overflow != NULL)
		str = search_line(overflow, fd, &size);
	else
	{	
		str = malloc((size + 1) * sizeof(char));
		if (!str)
			return (NULL);
		read(fd, str, size);
		str[size] = '\0';
		if (!str)
			return (NULL);
	tmp = search_line(str, fd, &size);
	}
	overflow = ft_memchr(tmp, '\n', size);
	overflow = overflow + 1;
	// printf("\nsize = %d\n", size);
	// printf("overflow = %s\n", overflow);
	return (str);
}
int	main(void)
{
	int f = open ("errr.txt", O_RDONLY);
	//get_next_line(f);
	printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	// printf("getnextline = %s", get_next_line(f));
	
	//printf("%s\n" , get_next_line(f));
	//// printf("%s\n" , get_next_line(f));
	close(f);
}