/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:54:11 by zlafou            #+#    #+#             */
/*   Updated: 2022/09/27 14:45:17 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == 0)
		return ((char *)(haystack));
	i = 0;
	while (haystack[i] && i <= len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len)
		{
			if (needle[j + 1] == 0)
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}

void	ft_checkfiles(char *file1)
{
	if (access(file1, F_OK | R_OK))
		perror(file1);
	exit(0);
}

void	ft_setpaths(char **ep, t_pipex *data)
{
	int		i;

	i = -1;
	while (ep[++i])
	{
		if (ft_strnstr(ep[i], "PATH=", 5))
		{
			data->alloc.paths = ft_split(ep[i] + 5, ':');
			ft_cleanup(!!data->alloc.paths, "malloc", *data);
		}
	}
}

void	ft_cleanup(long condition, char	*ermsg, t_pipex data)
{
	if (!condition)
	{
		ft_rwipe(data.alloc.paths, 2);
		ft_rwipe(data.alloc.cmdpaths, 2);
		ft_rwipe(data.alloc.spcmd, 3);
		if (ermsg)
			perror(ermsg);
		exit(!(!ermsg));
	}
}

void	ft_rwipe(void *ptr, int plvl)
{
	size_t	i;
	int		b;
	void	**p;

	p = (void **)ptr;
	b = 1;
	if (plvl < 0)
	{
		plvl *= -1;
		b = 0;
	}
	if (plvl > 1)
	{
		i = -1;
		while (p && p[++i])
		{
			if (plvl > 2)
				ft_rwipe((void **)p[i], -1 * (plvl - 1));
			free(p[i]);
		}
	}
	if (b)
		free(p);
}
