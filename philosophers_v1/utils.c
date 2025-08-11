#include "philo.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

void	free_philos(t_table *t)
{
	int		i;
	t_philo	**tab;

	tab = t->philos;
	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
}

void	free_forks(t_table *t)
{
	int		i;
	t_fork	**tab;

	tab = t->forks;
	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab && tab[i])
		free(tab[i]);
	if (tab)
		free(tab);
}
