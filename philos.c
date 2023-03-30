/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaskhan <tbaskhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:40:56 by tbaskhan          #+#    #+#             */
/*   Updated: 2023/03/30 12:35:52 by tbaskhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_datas(t_state *state, t_philo *philo, int id)
{
	philo->philo_thread = 0;
	philo->id = id + 1;
	philo->start = false;
	philo->fork = false;
	philo->eat = false;
	philo->sleep = false;
	philo->think = false;
	philo->alive = true;
	philo->meals_eaten = 0;
	philo->last_meal = 0;
	philo->datas = state->datas;
	philo->pprint = &state->print;
	philo->iinfo = &state->info;
	pthread_mutex_init(&philo->mutex, NULL);
}

void	previous_philo(t_state *state)
{
	int	id;
	int	previous;

	id = 0;
	while (id < state->datas->num_philo)
	{
		if (id == 0)
			previous = state->datas->num_philo - 1;
		else
			previous = id - 1;
		state->philos[id].previous = &state->philos[previous];
		id ++;
	}
}

void	create_philos(t_state *state)
{
	int	i;

	i = 0;
	state->philos = calloc(state->datas->num_philo, sizeof(t_philo));
	if (!state->philos)
	{
		perror("Failed calloc philos");
		free(state->datas);
		free(state);
		exit(1);
	}
	while (i < state->datas->num_philo)
	{
		set_datas(state, &state->philos[i], i);
		if (i % 2 == 0 && i != state->datas->num_philo -1)
				state->philos[i].start = true;
		i ++;
	}
	previous_philo(state);
}

void	init_philos(t_state *state)
{
	int		i;

	i = 0;
	state->datas->start_time = get_start_time();
	while (i < state->datas->num_philo)
	{
		if (pthread_create(&state->philos[i].philo_thread,
				NULL, &routine, (void *) &state->philos[i]) != 0)
		{
			return (error_philo(state, "thread creation"));
		}
		get_created(state, 1);
		i ++;
	}
}

void	join_philos(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->datas->num_philo)
	{
		if (pthread_join(state->philos[i].philo_thread, NULL))
		{
			error_philo(state, "join thread ");
			return ;
		}
		i ++;
	}
}
