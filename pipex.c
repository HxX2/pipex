/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:37:24 by zlafou            #+#    #+#             */
/*   Updated: 2022/06/06 10:55:07 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **ep)
{
	t_pipex	data;
	// pid_t	pid;

	ft_memset(&data, 0, sizeof(data));
	if (ac < 5)
	{
		ft_fprintf(1, "not enough arguments\n");
		exit(1);
	}
	if (!ft_strcmp(av[1], "here_doc"))
	{
		av++;
		ac--;
	}

	data.file1 = av[1];
	data.file2 = av[ac - 1];
	ft_checkfiles(data.file1);
	data.cmd = &av[2];
	data.cmd[ac - 3] = NULL;
	ft_setpaths(ep, &data);
	ft_setspcmd(&data);
	ft_setcmdpaths(&data);

	ft_execute(data,ep);

	// printdata(data);
	// ft_cleanup(0, NULL, data);
}

void	ft_setcmdpaths(t_pipex *data)
{
	int	i;

	data->alloc.cmdpaths = ft_calloc((data->ncmd + 1) * sizeof(char *));
	ft_cleanup(!!data->alloc.cmdpaths, "malloc", *data);
	i = -1;
	while (data->cmd[++i])
	{
		if (ft_strchr(data->alloc.spcmd[i][0], '/'))
			data->alloc.cmdpaths[i] = ft_strdup(data->alloc.spcmd[i][0]);
		else
			ft_checkpaths(data, i);
	}
}

void	ft_checkpaths(t_pipex *data, int i)
{
	char	*cmpath;
	int		j;

	j = -1;
	while (data->alloc.paths[++j])
	{
		cmpath = ft_joinpath(data->alloc.paths[j], data->alloc.spcmd[i][0]);
		ft_cleanup(!!cmpath, "malloc", *data);
		if (!access(cmpath, F_OK))
			data->alloc.cmdpaths[i] = cmpath;
		else if (!data->alloc.cmdpaths[i])
		{
			free(cmpath);
			data->alloc.cmdpaths[i] = ft_strdup("");
			ft_cleanup(!!data->alloc.cmdpaths[i], "malloc", *data);
		}
	}
}

void	ft_setspcmd(t_pipex *data)
{
	int		ncmd;
	char	***spcmd;
	int		i;

	ncmd = 0;
	while (data->cmd[ncmd])
		ncmd++;
	data->ncmd = ncmd;
	spcmd = ft_calloc((ncmd + 1) * sizeof(char **));
	ft_cleanup(!!spcmd, "malloc", *data);
	i = -1;
	while (data->cmd[++i])
	{
		spcmd[i] = ft_split(data->cmd[i], ' ');
		ft_cleanup(!!spcmd[i], "malloc", *data);
	}
	data->alloc.spcmd = spcmd;
}
 