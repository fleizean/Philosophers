/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:41:45 by eyagiz            #+#    #+#             */
/*   Updated: 2022/08/18 13:41:45 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(t_data *data)
{
	t_philo	*philo; // çok boyutlu filozof yeri açıyorum
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->num_philo); // filozof sayım kadar yer açıyorum
	while (i < data->num_philo)
	{
		philo[i].philo_id = i + 1; // filozofuma id tanımlaması yapıyorum
		philo[i].left_fork = i; // soldaki çatalını belirliyorum
		philo[i].right_fork = i + 1; // sağdaki çatalını belirliyorum
		philo[i].last_meal = get_time(); // en son yemek zamanını veriyorum, şu an 0 olarak girildi
		philo[i].ate = 0; // yediği yemek sayacını 0'dan başlatıyorum
		philo[i].data_of_philo = data; // filozofumun sahip olduğu data bilgilerini atıyorum
		pthread_mutex_init(&data->fork_lock[i], NULL); // tanımladığım mutex'i başlattığımı belirtiyorum.
		i++;
	}
	i--;
	philo[i].right_fork = 0; // en sonuncu filozofumun sağ çatalına 0 veriyorum ki 2 çatalı olsun.
	return (philo);
}

int	init_data(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6) // argüman sayımı init_data'da kontrol ettirme sebebim buradaki herhangi bir atoi kontrolünde sıkıntı yaşarsa segmentasyon sorunu alabileceğim yüzündendi
	{
		printf("Error: Incorrect count of argument.\n");
		return (-1); // eğer hata durumu varsa return (-1) diyerek mainde kontrolünü sağladığım yere yönlendirme yapıyorum, burada return atsam sonsuz loopda program çalışırdı.
	}
	data->num_philo = ft_atoi(av[1]); // filozof sayımı atadığım yer
	if (data->num_philo == 1)
	{
		printf("Philo 1 died.\n");
		return (-1);
	}
	data->t_die = ft_atoi(av[2]); // ne kadar süre yemek yemezse ölecek
	data->t_eat = ft_atoi(av[3]); // ne kadar süre arayla yemek yiyecek
	data->t_sleep = ft_atoi(av[4]); // ne kadar süre uyuyacak
	data->must_eat = 0; // must_eat'i başta 0 yapıyorum opsiyonel olarak alttaki if'e girerse değişecek
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]); // must_eat varsa must_eat atanacak.
	data->is_died = 0; // is_died durumu başta 0 olmalı
	data->sum_meal = 0; //
	data->fork_lock = malloc(sizeof(pthread_mutex_t) * data->num_philo); // her filozofum için çatal kilidi açtığım yer
	pthread_mutex_init(&data->print_lock, NULL); //
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data; // bütün filozoflarım içinki durum structı
	t_philo	*philo; // filozofların bilgilerini içeren struct

	if (init_data(&data, ac, av) == -1) // data structımın değerlerini atadığım yer <<
		return (0);
	if (check_args(&data) == -1) // argüman kontrollerini sağladığım yer <<
		return (0);
	philo = init_philo(&data); // filozoflarımın değerlerini atadığım yer
	if (start_dinner(philo) == -1) // yemeğin başladığı yer
		return (0);
	fin_dinner(philo, &data);
	return (0);
}
