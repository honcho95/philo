/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaskhan <tbaskhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:40:37 by tbaskhan          #+#    #+#             */
/*   Updated: 2023/03/30 11:40:38 by tbaskhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_philo *philo, size_t time)
{
	unsigned int	div;

	div = 0;
	while ((div + 50) < time)
	{
		usleep(50 * 1000);
		div += 50;
		if (!get_alive(philo, 2))
			return ;
	}
	usleep((time - div) * 1000);
}

static void	init_state(t_state *state, t_data *datas)
{
	state->monitor = 0;
	state->datas = datas;
	state->done_eat = -1;
	state->end = 0;
	state->philos_created = 0;
	pthread_mutex_init(&state->print, NULL);
	pthread_mutex_init(&state->info, NULL);
}

static void	philosophers(t_state *state)
{
	create_philos(state);
	if (pthread_create(&state->monitor, NULL, &check_alive, (void *) state))
	{
		free_state(state);
		exit(1);
	}
	init_philos(state);
	pthread_join(state->monitor, NULL);
	join_philos(state);
}

int	main(int ac, char **av)
{
	t_state		*state;
	t_data		*datas;

	datas = parsing(ac, av);
	state = (t_state *) calloc(1, sizeof(t_state));
	if (state)
	{
		init_state(state, datas);
		philosophers(state);
		free_state(state);
	}
	else
		free(datas);
	return (0);
}
