/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:10:58 by zlafou            #+#    #+#             */
/*   Updated: 2022/09/27 18:11:48 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static	void	ft_filter(t_pipex data, int i)
{
	if (!data.alloc.cmdpaths[i][0])
	{
		ft_fprintf(2, "pipex: %s: command not found\n", data.alloc.spcmd[i][0]);
		ft_cleanup(0, NULL, data);
		exit(1);
	}
	if (access(data.alloc.cmdpaths[i], F_OK | R_OK))
	{
		ft_fprintf(2, "pipex: %s: No such file or directory\n",
			data.alloc.spcmd[i][0]);
		ft_cleanup(0, NULL, data);
		exit(1);
	}
	if (access(data.alloc.cmdpaths[i], X_OK))
	{
		ft_fprintf(2, "pipex: %s: Permission denied\n", data.alloc.spcmd[i][0]);
		ft_cleanup(0, NULL, data);
		exit(1);
	}
}

static	void	ft_endfiles(t_pipex data)
{
	int		doc[2];
	int		fd;

	if (data.deli)
	{
		pipe(doc);
		ft_heredoc(data.deli, doc[1]);
		fd = dup(doc[0]);
		close(doc[1]);
	}
	else
		fd = open(data.file1, O_RDONLY);
	dup2(fd, 0);
	close(fd);
	if (data.deli)
		fd = open(data.file2, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(data.file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

static	void	ft_child(t_pipex data, int i, int *std, char **ep)
{
	if (i == 0 && access(data.file1, F_OK | R_OK) && !data.deli)
		ft_checkfiles(data.file1);
	ft_filter(data, i);
	if (i != data.ncmd - 1)
		dup2(std[1], 1);
	close(std[0]);
	close(std[1]);
	execve(data.alloc.cmdpaths[i], data.alloc.spcmd[i], ep);
}

void	ft_execute(t_pipex data, char **ep)
{
	int		std[2];
	pid_t	pid;
	int		i;

	i = -1;
	ft_endfiles(data);
	while (i++ != data.ncmd - 1)
	{
		if (i != data.ncmd - 1)
			pipe(std);
		pid = fork();
		ft_cleanup(pid != -1, "fork", data);
		if (pid == 0)
			ft_child(data, i, std, ep);
		if (i != data.ncmd - 1)
			dup2(std[0], 0);
		close(std[0]);
		close(std[1]);
	}
	close(0);
	while (wait(NULL) != -1)
		;
}
