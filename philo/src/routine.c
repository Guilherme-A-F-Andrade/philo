/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:52:32 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/26 16:35:33 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	one_case(t_philo *p)
{
	pthread_mutex_lock(&args()->prio);
	printf("%ld %i has taken a fork\n", time_now(), p->id);
	pthread_mutex_unlock(&args()->prio);
}

void	print_messages(t_philo *p, char c)
{
	if (!check_stop() && c == 't')
	{
		pthread_mutex_lock(&args()->prio);
		printf("%ld %d is thinking\n", time_now(), p->id);
		pthread_mutex_unlock(&args()->prio);
	}
	else if (!check_stop() && c == 's')
	{
		pthread_mutex_lock(&args()->prio);
		printf("%ld %d is sleeping\n", time_now(), p->id);
		pthread_mutex_unlock(&args()->prio);
		
	}
	else if (!check_stop() && c == 'e')
	{
		pthread_mutex_lock(&args()->prio);
		printf("%ld %d is eating\n", time_now(), p->id);
		pthread_mutex_unlock(&args()->prio);
	}

}

void	thinking(t_philo *p)
{
	if (check_stop())
		return ;
	print_messages(p, 't');
	usleep(1);
}

void	sleeping(t_philo *p)
{
	if (check_stop())
		return ;
	print_messages(p, 's');
	usleep(args()->time_to_s * 1000);
	
}

void	eating(t_philo *p)
{
	if (check_stop())
		return ;
	if (!get_forks(p))
		return ;
	print_messages(p, 'e');
	if (args()->nb_times_e > 0)
		p->n_meals++;
	pthread_mutex_lock(&args()->prio);
	p->last_meal = time_now();
	pthread_mutex_unlock(&args()->prio);
	//printf("philo[%d] nb meals: %d\n", p->id, p->n_meals);//to remove
	usleep(args()->time_to_e * 1000);
	drop_forks(p);
}

void	*start(void *arg)
{
	t_philo		*p;
	
	if (!arg)
		return (NULL);
	p = (t_philo *)arg;
	if (args()->nb_philo == 1)
		return (one_case(p), NULL);
	if ((p->id % 2) == 0)
		usleep(100);
	while (1)
	{
		if (args()->nb_times_e > 0 && p->n_meals >= args()->nb_times_e)
			break ;
		if (check_stop())
			break ;
		eating(p);
		if (check_stop())
			break ;
		sleeping(p);
		if (check_stop())
			break ;
		thinking(p);
	}
	return (NULL);
}
