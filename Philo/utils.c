/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:57:30 by eyagiz            #+#    #+#             */
/*   Updated: 2022/08/18 13:57:30 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	nbr;
	int	i;
	int	sign;

	nbr = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
			nbr = (nbr * 10) + (str[i++] - '0');
	}
	return (nbr * sign);
}

void	print(t_philo *philo, char *state)
{
	long	current_time;

	current_time = get_time() - philo->data_of_philo->start_time;
	pthread_mutex_lock(&philo->data_of_philo->print_lock);
	if (!philo->data_of_philo->is_died)
		printf("%3ld %3d %s\n", current_time, philo->philo_id, state);
	pthread_mutex_unlock(&philo->data_of_philo->print_lock);
}

int	check_args(t_data *data)
{
	if (data->num_philo < 1 || data->t_die < 1
		|| data->t_eat < 1 || data->t_sleep < 1)
	{
		printf("Error: Incorrect arguments.\n");
		return (-1);
	}
	return (1);
}

int	check_meals(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data_of_philo->must_eat > 0)
	{
		while (i < philo->data_of_philo->num_philo)
		{
			if (philo[i].ate >= philo->data_of_philo->must_eat)
				philo->data_of_philo->sum_meal++;
			i++;
		}
		if (philo->data_of_philo->sum_meal >= philo->data_of_philo->num_philo)
		{
			philo->data_of_philo->is_died = 1;
			return (1);
		}
	}
	return (0);
}
