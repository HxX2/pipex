/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:41:38 by zlafou            #+#    #+#             */
/*   Updated: 2022/06/06 10:55:49 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_alloc
{
	char	**paths;
	char	**cmdpaths;
	char	***spcmd;
}		t_alloc;

typedef struct s_pipex
{
	char	*file1;
	char	*file2;
	char	**cmd;
	int		ncmd;
	t_alloc	alloc;
}		t_pipex;

void	ft_cleanup(long condition, char	*ermsg, t_pipex	data);
char	*ft_joinpath(char const *s1, char const *s2);
void	ft_checkfiles(char	*file1);
void	ft_setpaths(char **ep, t_pipex *data);
void	ft_checkpaths(t_pipex *data, int i);
void	ft_setcmdpaths(t_pipex	*data);
void	ft_rwipe(void *ptr, int plvl);
void	ft_setspcmd(t_pipex *data);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);

char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t count);

int		ft_fprintf(int fd, const char *str, ...);

void	printdata(t_pipex data);
void	ft_execute(t_pipex data, char **ep);
#endif
