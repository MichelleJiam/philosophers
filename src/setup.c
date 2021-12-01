/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/19 15:57:20 by mjiam         #+#    #+#                 */
/*   Updated: 2021/07/19 15:57:20 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid_setup(t_setup *setup)
{
	if (setup->num_philo < 1 || setup->num_philo > 200
		|| setup->msec_to_die < 60
		|| setup->msec_to_eat < 60
		|| setup->msec_to_sleep < 60
		|| setup->must_eat < 0)
		return (false);
	return (true);
}

int	fill_setup(t_setup *setup, int *converted_args)
{
	setup->num_philo = converted_args[0];
	setup->msec_to_die = converted_args[1];
	setup->msec_to_eat = converted_args[2];
	setup->msec_to_sleep = converted_args[3];
	setup->must_eat = converted_args[4];
	return (0);
}

int	parse_args_into_setup(t_setup *setup, const char **args)
{
	int	i;
	int	converted_args[5];

	i = 0;
	while (args[i] != NULL)
	{
		converted_args[i] = 0;
		if (!valid_atoia(args[i], &converted_args[i]))
			return (1);
		i++;
	}
	if (i == 4)
		converted_args[4] = 0;
	if (fill_setup(setup, converted_args))
		return (1);
	if (!valid_setup(setup))
		return (1);
	return (0);
}
