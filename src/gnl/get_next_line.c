/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:24:05 by zlafou            #+#    #+#             */
/*   Updated: 2022/06/20 22:24:05 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	ft_clean(char **p)
{
	free(*p);
	*p = NULL;
}

static char	*ft_line(char **lines)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	if (!ft_strchr(*lines, '\n'))
	{
		line = ft_strdup(*lines);
		ft_clean(lines);
	}
	else
	{
		while ((*lines)[i] && (*lines)[i] != '\n')
			i++;
		line = ft_substr(*lines, 0, i + 1);
		temp = *lines;
		*lines = ft_strdup(&(*lines)[i + 1]);
		ft_clean(&temp);
	}
	if (!*line)
		ft_clean(&line);
	return (line);
}

static char	*ft_sew(int fd, char **lines, char **buff)
{
	char	*temp;
	ssize_t	rd;

	rd = 1;
	while (rd && !ft_strchr(*lines, '\n'))
	{
		rd = read(fd, *buff, BUFFER_SIZE);
		(*buff)[rd] = '\0';
		temp = *lines;
		*lines = ft_strjoin(*lines, *buff);
		ft_clean(&temp);
	}
	ft_clean(buff);
	return (ft_line(lines));
}

char	*get_next_line(int fd)
{
	static char	*lines = NULL;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (read(fd, buff, 0) == -1)
	{
		ft_clean(&buff);
		return (NULL);
	}
	if (!lines)
		lines = ft_strdup("");
	return (ft_sew(fd, &lines, &buff));
}
