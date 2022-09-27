/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:28:49 by zlafou            #+#    #+#             */
/*   Updated: 2022/09/27 06:24:57 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_heredoc(char *del, int fd)
{
	char	*line;
	char	*lines;
	char	*deli;
	char	*tmp;

	ft_fprintf(1, "heredoc> ");
	line = get_next_line(0);
	lines = ft_strdup("");
	deli = ft_strjoin(del, "\n");
	while (ft_strcmp(line, deli))
	{
		tmp = ft_strjoin(lines, line);
		free(lines);
		lines = tmp;
		free(line);
		ft_fprintf(1, "heredoc> ");
		line = get_next_line(0);
	}
	ft_fprintf(fd, "%s", lines);
	free(lines);
	free(deli);
}