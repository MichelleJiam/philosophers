/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjiam <mjiam@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 15:15:13 by mjiam         #+#    #+#                 */
/*   Updated: 2021/06/24 15:15:13 by mjiam         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*get_philo_colour(int philo_seat)
{
	static const char	*colour[] = {RED, GRN, YEL, BLU, MAG, CYN};

	return (colour[philo_seat % 6]);
}

int	ft_strcmp(void *s1, void *s2)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	str1 = s1;
	str2 = s2;
	while ((str1[i] && str2[i]) && str1[i] == str2[i])
		i++;
	if (!str1[i] && !str2[i])
		return (0);
	return (str1[i] - str2[i]);
}

bool	is_whitespace(const char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

int	ft_skipws(const char **str, int i)
{
	if (*str == NULL || *str[i] == '\0' || !is_whitespace(*str[i]))
		return (0);
	while (is_whitespace(*str[i]))
		(*str)++;
	return (1);
}

/* Converts num_str to int representation and saves in *num arg. 
Returns TRUE on success. If invalid input or outside int limits, 
returns FALSE and doesn't change *num. */

bool	valid_atoia(const char *num_str, int *num)
{
	bool		is_negative;
	intmax_t	res;

	res = 0;
	if (!num_str)
		return (false);
	ft_skipws(&num_str, 0);
	is_negative = (*num_str == '-');
	if (*num_str == '-' || *num_str == '+')
		num_str++;
	while (*num_str != '\0')
	{
		if (*num_str < '0' || *num_str > '9')
			return (false);
		res = res * 10 + (*num_str - '0');
		if ((!is_negative && res > INT_MAX)
			|| (is_negative && -(res) < INT_MIN))
			return (false);
		num_str++;
	}
	if (is_negative)
		*num = res * -1;
	else
		*num = res;
	return (true);
}
