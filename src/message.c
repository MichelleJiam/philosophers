/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 17:22:00 by mjiam         #+#    #+#                 */
/*   Updated: 2021/09/29 18:05:42 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_dead(t_philo *philo)
{
	if (lock_check(philo, &philo->setup->dead_lock, "set_dead") != 0)
		return (1);
	philo->setup->someone_dead = true;
	pthread_mutex_unlock(&philo->setup->dead_lock);
	return (0);
}

void	print_message(t_philo *philo, const char *message, t_msg_type type)
{
	uintmax_t	time;

	time = retrieve_time_since_ms(philo->setup->program_start_ms);
	printf("%s", get_philo_colour(philo->seat));
	printf("%ju\tphilosopher [%d] %s.", time, philo->seat, message);
	if (philo->setup->must_eat && type == EAT)
		printf(" (%d/%d)", philo->times_eaten + 1, philo->setup->must_eat);
	printf("\n%s", WHT);
}

int	status_change_message(t_philo *philo, const char *message, t_msg_type type)
{
	if (lock_check(philo, &philo->setup->msg_lock,
			"status_change_message") != 0)
		return (1);
	if (!gameover(philo))
	{
		print_message(philo, message, type);
		if (type == DEAD)
			set_dead(philo);
	}
	pthread_mutex_unlock(&philo->setup->msg_lock);
	return (0);
}
