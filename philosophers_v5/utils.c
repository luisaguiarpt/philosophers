#include "philo.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = (unsigned char)c;
	return (s);
}

static void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;

	ptr = malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}

void	*safe_calloc(size_t nmemb, size_t size, t_table *t)
{
	unsigned char	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		exit_error(t, CALLOCFAIL);
	return ((void *)ptr);
}
