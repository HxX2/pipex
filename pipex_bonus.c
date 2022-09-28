/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:37:24 by zlafou            #+#    #+#             */
/*   Updated: 2022/09/28 07:37:45 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **ep)
{
	t_pipex	data;

	ft_memset(&data, 0, sizeof(data));
	if (ac < 5)
		(ft_fprintf(1, "not enough arguments\n"), exit(1));
	data.file1 = av[1];
	data.file2 = av[ac - 1];
	if (!ft_strcmp(av[1], "here_doc"))
	{
		data.deli = av[2];
		data.cmd = &av[3];
		data.cmd[ac - 4] = NULL;
	}
	else
	{
		data.cmd = &av[2];
		data.cmd[ac - 3] = NULL;
	}
	ft_setpaths(ep, &data);
	ft_setspcmd(&data);
	ft_setcmdpaths(&data);
	ft_execute(data, ep);
	return (0);
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
		if (!data->alloc.cmdpaths[i])
		{
			data->alloc.cmdpaths[i] = ft_strdup("");
			ft_cleanup(!!data->alloc.cmdpaths[i], "malloc", *data);
		}
	}
}

void	ft_checkpaths(t_pipex *data, int i)
{
	char	*cmpath;
	int		j;

	j = -1;
	while (data->alloc.paths[++j])
	{
		if (!ft_strcmp(data->alloc.spcmd[i][0], ""))
		{
			data->alloc.cmdpaths[i] = ft_strdup("");
			return ;
		}
		cmpath = ft_joinpath(data->alloc.paths[j], data->alloc.spcmd[i][0]);
		ft_cleanup(!!cmpath, "malloc", *data);
		if (!access(cmpath, F_OK))
			data->alloc.cmdpaths[i] = cmpath;
		else
			free(cmpath);
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
		if (!spcmd[i][0])
		{
			spcmd[i] = ft_calloc(2 * sizeof(char *));
			spcmd[i][0] = ft_strdup("");
		}
		ft_cleanup(!!spcmd[i], "malloc", *data);
	}
	data->alloc.spcmd = spcmd;
}
