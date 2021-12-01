/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/16 21:20:18 by mjiam         #+#    #+#                 */
/*   Updated: 2021/09/29 17:48:11 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_full_philo(t_philo *philo)
{
	status_change_message(philo, MSG_ENOUGH, ENOUGH);
	philo->setup->full_philos++;
	return (NULL);
}

void	*handle_death(t_philo *philo)
{
	status_change_message(philo, MSG_DIED, DEAD);
	pthread_mutex_unlock(&philo->eat_lock);
	philo_clean_forks(philo);
	return (NULL);
}

void	*philo_check(void *philo_arg)
{
	t_philo		*philo;
	uintmax_t	current_time;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		if (!philo->active)
			break ;
		if (lock_check(philo, &philo->eat_lock, "philo_check") != 0)
			return ((void *)1);
		current_time = retrieve_time_since_ms(0);
		if (current_time > philo->deadline)
			return (handle_death(philo));
		pthread_mutex_unlock(&philo->eat_lock);
		if (philo->setup->must_eat > 0 && has_eaten_enough(philo))
			return (handle_full_philo(philo));
		usleep(1000);
	}
	return (NULL);
}
