/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbaskhan <tbaskhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:41:00 by tbaskhan          #+#    #+#             */
/*   Updated: 2023/03/30 12:35:43 by tbaskhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_start_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned long	get_time(unsigned long start)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

void	print_infos(t_philo *philo, int status)
{
	unsigned long	time;
	char			*str;

	time = philo->datas->start_time;
	if (status == 2)
		str = "is sleeping";
	else if (status == 1)
		str = "is eating";
	else if (status == 0)
		str = "is thinking";
	if (get_alive(philo, 2))
	{
		pthread_mutex_lock(philo->pprint);
		printf("%lu %d %s\n", get_time(time), philo->id, str);
		pthread_mutex_unlock(philo->pprint);
	}
}

void	print_fork(t_philo *philo, int status)
{
	unsigned long	time;

	time = philo->datas->start_time;
	if (get_alive(philo, 2))
	{
		pthread_mutex_lock(philo->pprint);
		printf("%lu %d has taken a fork\n", get_time(time), philo->id);
		if (status)
			printf("%lu %d has taken a fork\n", get_time(time), philo->id);
		pthread_mutex_unlock(philo->pprint);
	}
}

void	print_end(t_state *state, int status)
{
	unsigned long	time;

	time = state->datas->start_time;
	pthread_mutex_lock(&state->print);
	printf("%lu %d died\n", get_time(time), status);
	pthread_mutex_unlock(&state->print);
}
