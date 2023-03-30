/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaskhan <tbaskhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:41:03 by tbaskhan          #+#    #+#             */
/*   Updated: 2023/03/30 12:36:21 by tbaskhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	eating(t_philo *philo)
{
	print_fork(philo, 1);
	print_infos(philo, 1);
	set_fork(philo, 1);
	set_fork(philo->previous, 1);
	get_last_meal(philo, 1);
	philo->eat = true;
	ft_usleep(philo, philo->datas->time_to_eat);
	philo->eat = false;
	set_fork(philo, 0);
	set_fork(philo->previous, 0);
	set_meal(philo, 1);
	return (1);
}

static	int	sleep_n_think(t_philo *philo)
{
	print_infos(philo, 2);
	philo->sleep = true;
	ft_usleep(philo, philo->datas->time_to_sleep);
	philo->sleep = false;
	usleep(1000);
	print_infos(philo, 0);
	philo->think = true;
	return (1);
}

static int	cycle(t_philo *philo)
{
	if (set_fork(philo, -1) || set_fork(philo->previous, -1))
		return (1);
	philo->think = false;
	philo->start = false;
	eating(philo);
	sleep_n_think(philo);
	return (1);
}

void	*routine(void *philo_tmp)
{
	t_philo	*philo;

	philo = philo_tmp;
	if (philo->previous->id == philo->id)
	{
		print_fork(philo, 0);
		ft_usleep(philo, philo->datas->time_to_die);
		return (NULL);
	}
	while (get_alive(philo, 2))
	{
		if (!philo->start)
		{
			usleep(100);
			philo->start = true;
		}
		cycle(philo);
	}
	return (NULL);
}
