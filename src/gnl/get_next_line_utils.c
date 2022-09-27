/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 22:24:01 by zlafou            #+#    #+#             */
/*   Updated: 2022/06/20 22:24:01 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	dup = (char *)malloc(sizeof(*s1) * i + 1);
	if (!dup)
		return (0);
	j = 0;
	while (s1[j])
	{
		dup[j] = s1[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != (char)c && s[i])
		i++;
	if (i == ft_strlen(s) && s[i] != c)
		return (0);
	return ((char *)(s + i));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!s)
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	j = -1;
	i -= 1;
	while (s2[++j])
		s[++i] = s2[j];
	s[i + 1] = 0;
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		i;
	size_t		sl;

	if (!s)
		return (0);
	sl = ft_strlen(s);
	if (start > sl)
		start = sl;
	if (start + len > sl)
		len = sl - start;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	i = -1;
	s += start;
	while (s[++i] && i < len)
		ptr[i] = s[i];
	ptr[i] = 0;
	return (ptr);
}
