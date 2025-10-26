/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:52:01 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/26 15:32:01 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"
//args()->philos + i ultimo arg do thread create	

bool	innit_threads(void)
{
	int		i;

	i = 0;
	while (i < args()->nb_philo)
	{
		//printf(" philo nb %d\n", i);//to remove
		if (pthread_create(args()->threads + i, NULL, &start, args()->philos + i))
			return (false);
		//printf("adress thread[%i]:%p\n", i, &args()->threads + i);//to remove
		i++;
	}
	return (true);
}
t_philo		innit_philos(int i)
{
	t_philo		philo;

	philo.id = i;
	philo.n_meals = 0;
	philo.last_meal = time_now();
	return (philo);
}

bool	innit_mutexes(void)
{
	int		i;
	
	i = 0;
	while (i < args()->nb_philo)
	{
		args()->philos[i] = innit_philos(i);
		pthread_mutex_init(&args()->forks[i], NULL);
		//printf("fork[%i] adress: %p\n", i, &args()->forks[i]);//to remove
		i++;
	}
	pthread_mutex_init(&args()->prio, NULL);
	pthread_mutex_init(&args()->god, NULL);
	//printf("prio adress: %p\n", &args()->prio);//to remove
	return (true);
}

bool	innit_structs(void)
{
	int		i;
	args()->threads = (pthread_t *)malloc((args()->nb_philo) * sizeof(pthread_t));
	if (!args()->threads)
	return (false);
	//printf("threads[] adress: %p\n", args()->threads);//to remove
	args()->forks = (pthread_mutex_t *)malloc((args()->nb_philo) * sizeof(pthread_mutex_t));
	//printf("forks[] adress: %p\n", args()->forks);//to remove
	if (!args()->forks)
	{
		free(args()->threads);
		args()->threads = NULL;
		return (false);
	}
	args()->philos = (t_philo *)malloc((args()->nb_philo) * sizeof(t_philo));
	//printf("philos[] adress: %p\n", args()->philos);//to remove
	if (!args()->philos)
	{
		free(args()->threads);
		args()->threads = NULL;
		free(args()->forks);
		args()->forks = NULL;
		return (false);
	}
	return (true);
}

bool	innit_everything(void)
{
	if (!innit_structs())
		return (false);
	args()->s_time = get_time();
	//printf("s_time: %ld\n", args()->s_time);//to remove
	if (!innit_mutexes())
	{
		return (false);
		//some form of clean
	}
	if (!innit_threads())
	{
	// 	some form of clean
		return (false);
	}
	return (true);
}