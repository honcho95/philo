#include "philo.h"

void	ft_putstr_fd(int fd, char *s)
{
	while (*s)
		write(fd, &(*s++), 1);
}

void	*ft_calloc(size_t n, size_t size)
{
	void		*ptr;
	size_t		max;
	size_t		i;

	i = 0;
	ptr = (void *) malloc(size * n);
	if (!ptr)
		return (NULL);
	max = n * size;
	while (i < max)
	{
		*(unsigned char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}

static void	free_mutex(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->datas->num_philo)
	{
		pthread_mutex_destroy(&state->philos[i].mutex);
		i ++;
	}
	pthread_mutex_destroy(&state->print);
	pthread_mutex_destroy(&state->info);
}

void	free_state(t_state *state)
{
	free_mutex(state);
	free(state->philos);
	free(state->datas);
	free(state);
}

void	error_philo(t_state *state, char *msg)
{
	perror(msg);
	kill_philos(state);
	return ;
}

