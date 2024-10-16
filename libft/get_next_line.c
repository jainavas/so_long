/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:16:53 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/09 15:05:37 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*readbuff(int fd, char *statstr)
{
	char	*x;
	int		numred;

	numred = 1;
	x = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!x)
		return (NULL);
	x[0] = '\0';
	while (numred > 0 && !ft_strchr_gnl(x, '\n'))
	{
		numred = read(fd, x, BUFFER_SIZE);
		if (numred > 0)
		{
			x[numred] = '\0';
			statstr = ft_strjoin_gnl(statstr, x);
		}
	}
	free(x);
	if (numred == -1)
		return (ft_free(&statstr));
	return (statstr);
}

char	*setnextstat(char *statstr, char *nextl)
{
	char	*newstat;
	int		len;

	if (nextl == NULL)
	{
		newstat = NULL;
		return (ft_free(&statstr));
	}
	else
		len = (nextl - statstr) + 1;
	if (!statstr[len])
		return (ft_free(&statstr));
	newstat = ft_substr_gnl(statstr, len, ft_strlen(statstr) - len);
	ft_free(&statstr);
	if (!newstat)
		return (NULL);
	return (newstat);
}

char	*get_next_line(int fd)
{
	static char	*statstr;
	char		*line;
	char		*ptr;

	if (fd < 0)
		return (NULL);
	if ((statstr && !ft_strchr_gnl(statstr, '\n')) || !statstr)
		statstr = readbuff(fd, statstr);
	if (!statstr)
		return (NULL);
	ptr = ft_strchr_gnl(statstr, '\n');
	line = ft_substr_gnl(statstr, 0, (ptr - statstr) + 1);
	if (!line)
		return (ft_free(&statstr));
	statstr = setnextstat(statstr, ptr);
	return (line);
}

// #include <fcntl.h>
// int main(void){
// 	int fd = open("hola.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// }