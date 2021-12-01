/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/29 17:38:51 by mjiam         #+#    #+#                 */
/*   Updated: 2021/09/29 17:39:41 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* returns time in microseconds */

uintmax_t	retrieve_time_us(void)
{
	struct timeval	time;
	uintmax_t		time_usec;

	gettimeofday(&time, NULL);
	time_usec = (time.tv_sec * 1000) * 1000;
	time_usec += time.tv_usec;
	return (time_usec);
}

/* returns time in miliseconds, minus optional start time */

uintmax_t	retrieve_time_since_ms(uintmax_t start)
{
	struct timeval	time;
	uintmax_t		time_msec;

	gettimeofday(&time, NULL);
	time_msec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (time_msec < start)
		return (0);
	return (time_msec - start);
}
