/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gclement <gclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:28:29 by gclement          #+#    #+#             */
/*   Updated: 2022/11/29 15:45:43 by gclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	if (!(s1 == NULL || s2 == NULL))
	{	
		dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
		if (!dest)
			return (NULL);
		ft_strlcpy(dest, ((char *)s1), (ft_strlen(s1) + 1));
		ft_strlcat(dest, s2, (ft_strlen(s1) + (ft_strlen(s2) + 1)));
		free ((char *)s2);
		free ((char *)s1);
		return (dest);
	}
	free ((char *)s1);
	free ((char *)s2);
	return (NULL);
}

char	*copy_line(char *str, int *bytes)
{
	char	*dest;
	int		i;

	i = 0;
	dest = NULL;
	if (ft_strchr(str, '\n') != 0 || *bytes != BUFFER_SIZE)
	{
		while (str[i] && str[i] != '\n')
			i++;
		i++;
		dest = malloc((i + 1) * sizeof(char));
		if (!dest)
			return (NULL);
		ft_strlcpy(dest, str, (i + 1));
	}
	return (dest);
}

char	*read_and_join(char *dest, int fd, int *bytes)
{
	char	*str;
	char	*tmp;
	int		tmp_bytes;

	if (fd < 0)
		return (NULL);
	tmp_bytes = *bytes;
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (*bytes != 0)
	{
		*bytes = read(fd, str, BUFFER_SIZE);
		str[*bytes] = '\0';
		//printf("str = %s\ndest = %s\nbytes = %d\n", str, dest, *bytes);
	}
	if (*bytes == 0 && tmp_bytes == -1)
		return (free (str), dest);
	if (dest != NULL && str != NULL)
	{
		tmp = ft_strjoin(dest, str);
		return (tmp);
	}
	return (str);
}

char	*search_line(char *str, int fd, int *bytes)
{
	if (str == NULL)
		return (NULL);
	while ((*bytes == BUFFER_SIZE || *bytes == -1)
		&& ft_strchr(str, '\n') == 0)
	{
		str = read_and_join(str, fd, bytes);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*overflow;
	char		*str;
	char		*tmp;
	int			bytes;

	bytes = -1;
	if (read(fd, NULL, 0) == -1)
		return (free(overflow), overflow = NULL, NULL);
	if (overflow != NULL)
		str = search_line(overflow, fd, &bytes);
	else
		str = read_and_join(NULL, fd, &bytes);
	if (str == NULL)
		return (NULL);
	str = search_line(str, fd, &bytes);
	tmp = copy_line(str, &bytes);
	if (ft_strchr(str, '\n') != 0 && str != NULL)
		overflow = ft_strdup(ft_strchr(str, '\n'));
	else
		overflow = NULL;
	if (tmp[0] == '\0' || tmp == NULL)
		return (free(str), free(tmp), NULL);
	//printf("tmp = %s\noverflow = %s\n", tmp, overflow);
	return (free(str), tmp);
}

// int	main(void)
// {
// 	int f = open ("7empty.txt", O_RDONLY);
// 	int count = 0;
// 	while (count < 6)
// 	{
// 		//get_next_line(f);
// 		printf("%s\n", get_next_line(f));
// 		//printf("\n-----------------------------------------------------------------\n");
// 		count++;
// 	}
// 	close(f);
// }
