/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:28:49 by zlafou            #+#    #+#             */
/*   Updated: 2022/09/28 07:41:17 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_heredoc(char *deli, int fd)
{
	char	*line;
	char	*lines;
	char	*tmp;

	ft_fprintf(1, "heredoc> ");
	line = get_next_line(0);
	if (!line)
		return ;
	lines = ft_strdup("");
	while (ft_strcmp(line, deli))
	{
		tmp = ft_strjoin(lines, line);
		free(lines);
		lines = tmp;
		free(line);
		ft_fprintf(1, "heredoc> ");
		line = get_next_line(0);
		if (!line)
			break ;
	}
	ft_fprintf(fd, "%s", lines);
	free(line);
	free(lines);
	free(deli);
}
