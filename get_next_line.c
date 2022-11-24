/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:28:29 by gclement          #+#    #+#             */
/*   Updated: 2022/11/24 10:26:20 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// void	memorize_line(int *i, int *tmp, char *all_file)
// {
// 	if (*tmp <= 0)
// 	{
// 		*i = 0;
// 		while (all_file[*i] != '\n')
// 			*i += 1;
// 	}
// 	else
// 	{
// 		printf(" else tmp = %d", *tmp);
// 		while (all_file[*i] != '\n')
// 			*i += 1;
// 	}
// 	*i += 1;
// 	*tmp = *i;
// 	printf("i = %d, tmp = %d\n", *i, *tmp);
// }

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

	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	read(fd, str, size);
	if (ft_memchr(str, '\0', size) != 0)
	{
		ft_bzero(ft_memchr(str, '\n', size), 2);
		return (ft_strjoin(dest, str));
	}
	str[size] = '\0';
	return (ft_strjoin(dest, str));
}

char	*get_next_line(int fd)
{
	char	*str;
	int		size;

	size = BUFFER_SIZE;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	read(fd, str, size);
	str[size] = '\0';
	if (!str)
		return (NULL);
	while (ft_memchr(str, '\n', size) == 0)
	{
		size += BUFFER_SIZE;
		str = allocate_and_read(str, fd, size);
	}
	ft_bzero(ft_memchr(str, '\n', size), 2);
	return (str);
}

int	main(void)
{
	int f = open ("7empty.txt", O_RDONLY);
	printf("%s" ,get_next_line(f));	
	close(f);
}