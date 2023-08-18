/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:17:07 by tabreia-          #+#    #+#             */
/*   Updated: 2022/11/24 15:27:10 by tabreia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_read_to_glbstr(int fd, char *glbstr)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr_gnl(glbstr, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(glbstr);
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		glbstr = ft_strjoin_gnl(glbstr, buff);
	}
	free(buff);
	return (glbstr);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*glbstr[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	glbstr[fd] = ft_read_to_glbstr(fd, glbstr[fd]);
	if (!glbstr[fd])
		return (NULL);
	line = ft_get_line(glbstr[fd]);
	glbstr[fd] = ft_new_glbstr(glbstr[fd]);
	return (line);
}
