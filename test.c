#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

/*
	Fonction pour transformer l'env natif en copie sur laquelle on travaillera
*/
char	**ft_get_env_copy(char	**envp)
{
	int lenght;
	int i;
	int	len;
	char	**env_copy;

	lenght = 0;
	len = 0;
	i = 0;

	while(envp[lenght])
	{
		printf("%s\n", envp[lenght]);
		lenght++;
	}
	printf("\n\n\n");
	env_copy = malloc(sizeof(char **) * lenght + 1);
	while (i < lenght)
	{
		len = ft_strlen(envp[i]);
		env_copy[i] = malloc(sizeof (char*) * len + 1);
		env_copy[i] = envp[i];
		i++;
	}
	i = 0;
	while(env_copy[i])
	{
		printf("%s\n", env_copy[i]);
		i++;
	}
	return(env_copy);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*resdst;
	char		*ressrc;

	if (dst == 0 && src == 0)
		return (0);
	resdst = (char *)dst;
	ressrc = (char *)src;
	i = 0;
	while (i < n)
	{
		resdst[i] = ressrc[i];
		i++;
	}
	return (resdst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1size;
	size_t	s2size;

	if (!s1 || !s2)
		return (0);
	s1size = ft_strlen(s1);
	s2size = ft_strlen(s2);
	res = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (res)
	{
		ft_memcpy(res, s1, s1size);
		ft_memcpy(res + s1size, s2, s2size + 1);
	}
	return (res);
}

/*
	Prends en parametre le PWD
	Renvois le new_PWD avec le strjoin du "readline"
*/

char	*comand_cd(char	*pwd)
{
	char	read_line[] = "incs";

	printf("\n\n\nvaleur de l'ancien PWD = %s\n", pwd);
	pwd = ft_strjoin(pwd, "/incs");
	printf("\n\n\nvaleur du nouveau PWD = %s\n", pwd);
	
}
/* Main pour avoir l'env natif */

int	main(int	argc, char	*argv[], char	*envp[])
{
	char	**env_copy;
	int i;

	i = 0;
	env_copy = ft_get_env_copy(envp);
	printf("\n\n\n");
	while(env_copy[i])
	{
		printf("%s\n", env_copy[i]);
		i++;
	}
	i = 0;
	while(env_copy[i])
	{
		if(strstr(env_copy[i], "PWD") != 0)
			break;
		i++;
	}
	comand_cd(env_copy[i]);
	//printf("\n\n\n%s\n", env_copy[i]);
}

/*
	Fonction test avec CD, change l'env copy 
	=> PWD
	avec un STRJOIN
*/