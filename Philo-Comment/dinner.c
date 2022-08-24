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

void	fin_dinner(t_philo *philo, t_data *data) // komple oluşturduğum mutexleri destroylar ve malloc ile yer açılan yerleri freeler böylece leak engellenmiş olur.
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
	pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->left_fork]); // çatal kilidini gelen filozofa veriyorum böylece o filozof çatalı tutmuş oluyor 
	pthread_mutex_lock(&philo->data_of_philo->fork_lock[philo->right_fork]); // çatal kilidini gelen filozofa veriyorum böylece o filozof çatalı tutmuş oluyor 
	print(philo, "has taken left fork");
	print(philo, "has taken right fork");
	print(philo, "is eating");
	philo->last_meal = get_time(); // yemek yediği için last_meal'ına en son yemek yediği yeni süreyi atıyorum
	i_need_sleep(philo->data_of_philo->t_eat, philo); // yemek yerken ki geçecek süreyi veriyorum
	pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->left_fork]); // çatal kilidini açıyorum
	pthread_mutex_unlock(&philo->data_of_philo->fork_lock[philo->right_fork]); // çatal kilidini açıyorum
}

void	*loop(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr; // burası asceding yaptığım yer aslında dışarıdan aldığım void türündeki filozofumu t_philo türündeki değişkenime çeviriyorum
	if (philo->philo_id % 2 != 0) // tek sayı id'ye sahip filozoflarımı uyutuyorum
		usleep(1600);
	while (philo->data_of_philo->is_died != 1) // hiç bir filozofum ölmediyse girsin diyorum
	{
		eat_func(philo); // filozofuma yemek yediriyorum
		print(philo, "is sleeping"); 
		i_need_sleep(philo->data_of_philo->t_sleep, philo); // filozofu bana verilen vakit kadar uyutuyorum
		print(philo, "is thinking");
		usleep(1000);
		philo->ate++; // bir adet yemek yiyen filozofum olduğu için ate değişkenimi arttırıyorum
	}
	return (NULL);
}

void	*monitoring(void *ptr) // bu fonksiyonum dışarıdan izleyen bir insan gibi masayı kontrol ediyor.
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	while (!check_meals(philo)) // yemek kontrolünün yapıldığı yer must_eat / sum meal bağlantısı için
	{
		i = 0;
		while (i < (philo->data_of_philo->num_philo))
		{
			if (get_time() - philo[i].last_meal > philo->data_of_philo->t_die) // alınan zamandan last_meal süremi çıkarttığımda yenmesi gereken yemek süresini aşıyorsa filozofu öldürüp programı sonlandırıyorum
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
	pthread_t	monitor; // monitör için bir adet thread oluşturuyorum

	i = -1;
	philo->data_of_philo->start_time = get_time(); // yemeğin başladığı yer olacağı için yemeğin start_time'ını kaydediyorum
	while (++i < philo->data_of_philo->num_philo)
	{
		pthread_create(&philo[i].thread, NULL, &loop, &philo[i]); // her filozofumu loop fonksiyonuma gönderiyorum
	}
	pthread_create(&monitor, NULL, &monitoring, philo); // dışarıdan masayı izleyecek monitörümün threadini sisteme tanımlıyorum, oluşturuyorum.
	i = -1;
	while (++i < philo->data_of_philo->num_philo)
	{
		pthread_join(philo[i].thread, NULL); // pthread_join fonksiyonu bir threadın sonlanmasını bekletmeye yarar, threadin işlemi bitene kadar join programın bitmesini engeller diyebiliriz.
	}
	pthread_join(monitor, NULL); // pthread_join fonksiyonu bir threadın sonlanmasını bekletmeye yarar, threadin işlemi bitene kadar join programın bitmesini engeller diyebiliriz.
	return (1);
}
