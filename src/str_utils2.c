/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 10:54:33 by zlafou            #+#    #+#             */
/*   Updated: 2022/06/06 10:54:33 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (((s1[i] && s2[i]) && s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;
	char	*p;

	i = 0;
	while (s1[i])
		i++;
	dup = (char *)malloc(sizeof(*s1) * i + 1);
	if (!dup)
		return (0);
	p = dup;
	while (*s1)
		*(dup++) = *(s1++);
	*dup = 0;
	return (p);
}

void	*ft_calloc(size_t n)
{
	void		*ptr;

	ptr = malloc(n);
	if (!ptr)
		return (0);
	while (n)
		((unsigned char *)ptr)[--n] = 0;
	return (ptr);
}
