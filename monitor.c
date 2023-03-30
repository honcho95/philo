#include "philo.h"

//reset @ the end so the other philos can eat nb_meals times
static void	get_meals(t_state *state, int i)
{
	int	tmp;

	tmp = set_meal(&state->philos[i], -1);
	if (tmp == (int) state->datas->nb_meals)
	{
		++state->done_eat;
		set_meal(&state->philos[i], 0);
	}
}

static void	*check_end(t_state *state, int status)
{
	if (status > 0)
	{
		kill_philo(&state->philos[status -1]);
		print_end(state, status);
	}
	kill_philos(state);
	return (NULL);
}

void	kill_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->datas->num_philo)
	{
		get_alive(&state->philos[i], 0);
		i ++;
	}
}

void	kill_philo(t_philo *philo)
{
	get_alive(philo, 0);
}

void	*check_alive(void *state_tmp)
{
	t_state	*state;
	int		i;

	state = state_tmp;
	i = -1;
	while (get_created(state, 0) < state->datas->num_philo)
		usleep(500);
	while (1)
	{
		if (i < state->datas->num_philo - 1)
			i ++;
		else
			i = 0;
		get_meals(state, i);
		if (state->done_eat >= state->datas->num_philo - 1
				&& state->datas->nb_meals > 0)
			return (check_end(state, -1));
		if (get_last_meal(&state->philos[i], 0)
			+ state->datas->time_to_die < get_time(state->datas->start_time))
			return (check_end(state, state->philos[i].id));
		usleep(200);
	}
	return (NULL);
}

