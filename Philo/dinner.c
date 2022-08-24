/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:10:51 by eyagiz            #+#    #+#             */
/*   Updated: 2022/08/18 14:10:51 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fin_dinner(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->fork_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	free(data->fork_lock);
	free(philo);
}

void	eat_func(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->left_fork]);
	pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->right_fork]);
	print(philo, "has taken left fork");
	print(philo, "has taken right fork");
	print(philo, "is eating");
	philo->last_meal = get_time();
	i_need_sleep(philo->data_of_philo->t_eat, philo);
	pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->right_fork]);
}

void	*loop(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->philo_id % 2 != 0)
		usleep(1600);
	while (philo->data_of_philo->is_died != 1)
	{
		eat_func(philo);
		print(philo, "is sleeping");
		i_need_sleep(philo->data_of_philo->t_sleep, philo);
		print(philo, "is thinking");
		usleep(1000);
		philo->ate++;
	}
	return (NULL);
}

void	*monitoring(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	while (!check_meals(philo))
	{
		i = 0;
		while (i < (philo->data_of_philo->num_philo))
		{
			if (get_time() - philo[i].last_meal > philo->data_of_philo->t_die)
			{
				print(&philo[i], "died");
				philo->data_of_philo->is_died = 1;
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}

int	start_dinner(t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	philo->data_of_philo->start_time = get_time();
	while (++i < philo->data_of_philo->num_philo)
	{
		pthread_create(&philo[i].thread, NULL, &loop, &philo[i]);
	}
	pthread_create(&monitor, NULL, &monitoring, philo);
	i = -1;
	while (++i < philo->data_of_philo->num_philo)
	{
		pthread_join(philo[i].thread, NULL);
	}
	pthread_join(monitor, NULL);
	return (1);
}
