/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:30:42 by eyagiz            #+#    #+#             */
/*   Updated: 2022/08/18 13:30:42 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				sum_meal;
	long			start_time;
	int				is_died;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*fork_lock;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	long		last_meal;
	int			ate;
	int			philo_id;
	int			left_fork;
	int			right_fork;
	t_data		*data_of_philo;
}	t_philo;

//init
int		init_data(t_data *data, int ac, char **av);
t_philo	*init_philo(t_data *data);
//utils
int		check_args(t_data *data);
void	print(t_philo *philo, char *state);
long	get_time(void);
int		check_meals(t_philo *philo);
int		ft_atoi(char *ptr);
//dinner
void	fin_dinner(t_philo *philo, t_data *data);
void	eat_func(t_philo *philo);
void	*loop(void *ptr);
void	*monitoring(void *ptr);
int		start_dinner(t_philo *philo);
void	i_need_sleep(long long time, t_philo *sim);

#endif
