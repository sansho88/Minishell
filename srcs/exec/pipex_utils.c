/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgeral <rgeral@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:52:03 by tgriffit          #+#    #+#             */
/*   Updated: 2022/10/17 15:24:07 by rgeral           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	int		r;

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

int	ft_dup2(int a, int b)
{
	int	fd;

	fd = dup2(a, b);
	if (fd == -1)
	{
		perror("dup error");
		exit(127);
	}
	return (fd);
}

void	sort_tab_exec(t_args *d)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	/*while (d->sort_env[i])
	{
		
		while (j < d->env_len - 1 - i)
		{
			if (strcmp(d->sort_env[j], d->sort_env[j + 1]) > 0)
			{
				tmp = d->sort_env[j];
				d->sort_env[j] = d->sort_env[j + 1];
				d->sort_env[j + 1] = tmp;
			}
			j++;
		}
			//printf("sort_tab : %s\n", sort_tab[i]);
		j = 0;
		i++;
	}
}*/
	while (d->sort_env[i])
	{
		
		while (j < d->env_len - 1 - i)
		{
			if (strcmp(d->sort_env[j], d->sort_env[j + 1]) > 0)
			{
				tmp = ft_strdup(d->sort_env[j]);
				free(d->sort_env[j]);
				d->sort_env[j] = ft_strdup(d->sort_env[j + 1]);
				free(d->sort_env[j + 1]);
				d->sort_env[j + 1] = ft_strdup(tmp);
				free(tmp);
				/*strcpy(tmp, d->sort_env[j]);
       	 		strcpy(d->sort_env[j], d->sort_env[j+1]);
        		strcpy(d->sort_env[j+1], tmp);*/
			}
			j++;
		}
			//printf("sort_tab : %s\n", sort_tab[i]);
		j = 0;
		i++;
	}
}
