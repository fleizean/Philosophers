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
	int				num_philo; // filozof sayım
	int				t_die; // ne kadar süre yemek yemezse ölecek
	int				t_eat; // ne kadar süre arayla yemek yiyecek
	int				t_sleep; // ne kadar süre uyuyacak
	int				must_eat; // eğer verildiyse filozoflar ne kadar yemek yerse program sonlanacak
	int				sum_meal; // sum_meal değişkeni must_eat için tanımlanmış bir şey, filozof sayıma göre örnek olarak 2 kabul edelim ve must_eat 3 olsun. 
					// 1. filozofum 3 yemek yediyse sum_meal değişkeni 1 attırılır böylece filozoflarımın zorunlu yemek kısmını kontrol edebilirim.
	long			start_time; // yemeğe başlanan zamanı tutuyorum ki ekrana yazdırabileyim
	int				is_died; // ölüp ölmediğinin kontrolünü sağlıyorum. eğer 1 ise öldü 0 ise ölmedi.
	pthread_mutex_t	print_lock; // yazdırma kiliti için mutex tanımlıyorum
	pthread_mutex_t	*fork_lock; // çatal kiliti için mutex tanımlıyorum
}	t_data;

typedef struct s_philo
{
	pthread_t	thread; // bu yapımın bir thread tutması gerekiyor ki çoklu işlem yapabileyim
	long		last_meal; // en son yemek yediği zaman
	int			ate; // filozofumun yediği yemek count'ı 
	int			philo_id; // her filozfomun bir id'si olacak masa üzerinde.
	int			left_fork; // solundaki çatal id'sini tanımlıyorum.
	int			right_fork; // sağındaki çatal id'sini tanımlıyorum.
	t_data		*data_of_philo; // ve üstteki structımla bu structımı birleştiriyorum buradaki structtan o structtaki bir filozofa erişebileceğim
								// bağlı listeler diyebiliriz.
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
