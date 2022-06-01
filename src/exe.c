/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:10:58 by zlafou            #+#    #+#             */
/*   Updated: 2022/06/01 20:30:37 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_execute(t_pipex data, char **ep)
{
	int	fd;
	int std[2];
	pid_t pid;
	int i;
	int ret;

	i = -1;
	fd = open(data.file1, O_RDONLY);
	if (fd == -1 && i++)
		pipe(std);
	dup2(fd,0);
	close(fd);
	fd = open(data.file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd,1);
	close(fd);
	while (i++ != data.ncmd - 1)
	{
		if (i != data.ncmd - 1)
			pipe(std);
		pid = fork();
		ft_cleanup(pid != -1, "fork", data);
		if (pid == 0)
		{
			if (i != data.ncmd - 1)
				dup2(std[1], 1);
			if (i != 0)
				dup2(std[0], 0);
			close(std[1]);
			close(std[0]);
			if (!data.alloc.cmdpaths[i][0])
			{
				ft_fprintf(2,"pipex: %s: command not found\n", data.alloc.spcmd[i][0]);
				ft_cleanup(0, NULL, data);
				exit(1);
			}
			if (access(data.alloc.cmdpaths[i], F_OK | R_OK))
			{
				ft_fprintf(2,"pipex: %s: No such file or directory\n", data.alloc.spcmd[i][0]);
				ft_cleanup(0, NULL, data);
				exit(1);
			}
			if (access(data.alloc.cmdpaths[i], X_OK))
			{
				ft_fprintf(2,"pipex: %s: Permission denied\n", data.alloc.spcmd[i][0]);
				ft_cleanup(0, NULL, data);
				exit(1);
			}
			ret = execve(data.alloc.cmdpaths[i], data.alloc.spcmd[i], ep);
		}
	}
	close(std[0]);
	close(std[1]);
	while (wait(NULL) != -1)
		;
}