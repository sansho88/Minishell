#include "libft.h"

/**
 * Alloue (avec malloc(3)) et retourne une nouvelle chaine, résultat de la
 * concaténation de s1 et s2.
 * @param s1
 * @param s2
 * @return La nouvelle chaine de caractères. NULL si l’allocation échoue.
 */
char	*ft_strjoin_free(char *s1, char *s2, int s_to_free)
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
	if (s1 && *s1 && (s_to_free == 1 || s_to_free == 3))
		free(s1);
	if (s2 && *s2 && (s_to_free == 2 || s_to_free == 3))
		free(s2);
	return (res);
}
