/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_n_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaskhan <tbaskhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:40:40 by tbaskhan          #+#    #+#             */
/*   Updated: 2023/03/30 12:36:33 by tbaskhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_alive(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->iinfo);
	res = philo->alive;
	if (status == 1)
		philo->alive = true;
	else if (status == 0)
		philo->alive = false;
	pthread_mutex_unlock(philo->iinfo);
	return (res);
}

int	get_last_meal(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->iinfo);
	res = philo->last_meal;
	if (status == 1)
		philo->last_meal = get_time(philo->datas->start_time);
	pthread_mutex_unlock(philo->iinfo);
	return (res);
}

int	get_created(t_state *state, int status)
{
	int	res;

	pthread_mutex_lock(&state->print);
	res = state->philos_created;
	if (status)
		res = ++state->philos_created;
	pthread_mutex_unlock(&state->print);
	return (res);
}

int	set_meal(t_philo *philo, int status)
{
	int	res;

	pthread_mutex_lock(philo->pprint);
	res = philo->meals_eaten;
	if (!status)
		philo->meals_eaten = -1;
	if (status > 0 && philo->meals_eaten > -1)
		res = ++philo->meals_eaten;
	pthread_mutex_unlock(philo->pprint);
	return (res);
}

int	set_fork(t_philo *philo, int status)
{	
	int	res;

	pthread_mutex_lock(&philo->mutex);
	res = philo->fork;
	if (status == 1)
		philo->fork = true;
	else if (status == 0)
		philo->fork = false;
	pthread_mutex_unlock(&philo->mutex);
	return (res);
}
