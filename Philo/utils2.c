/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:43:06 by eyagiz            #+#    #+#             */
/*   Updated: 2022/08/19 16:04:18 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	i_need_sleep(long long time, t_philo *sim)
{
	long long	t;

	t = get_time();
	while (!(sim->data_of_philo->is_died))
	{
		usleep(32);
		if (get_time() - t >= time)
			break ;
	}
}
