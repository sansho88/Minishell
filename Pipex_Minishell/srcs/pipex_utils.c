/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:24:21 by rgeral            #+#    #+#             */
/*   Updated: 2022/04/20 13:35:51 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include "../incs/pipex.h"
#include <sys/types.h>
#include <sys/wait.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (len > i && s[start])
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		res[i++] = s2[j++];
	}
	res[i] = '\0';
	return (res);
}

int	ft_memcmp(const void	*po1, const void	*po2, size_t	size)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)po1;
	p2 = (unsigned char *)po2;
	i = 0;
	while (i < size)
	{
		if (p1[i] != p2[i])
			return ((unsigned char)p1[i] - (unsigned char)p2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	execute(t_args *p, char **args, int nb)
{
	char	*tmp;
	int		j;

	dprintf(1, "test");
	j = 0;
	/*
		Vérifie tout les path + fonction et check si c'est executable, si oui, execute, "sinon invalid path"
		ex : bin/ls
	*/
	while (p->path[j])
	{
		tmp = ft_strjoin(p->path[j], args[0]);
		if (access(tmp, F_OK | X_OK) == 0)
			break ;
		j++;
	}
	if (access(tmp, F_OK | X_OK) != 0 && nb < p->argc - 1)
	{
		perror("Invalid Path");
		exit(EXIT_FAILURE);
	}
	else if (tmp)
	{
		args[0] = tmp;
		execve(args[0], args, p->env);
	}
}

int	ft_dup2(int a, int b)
{
	int	fd;

	fd = dup2(a, b);
	return (fd);
}
