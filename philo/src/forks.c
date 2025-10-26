/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:51:47 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/26 16:26:23 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

void	print_fork_assignment(t_philo *p)//to remove
{
	int	forks[2];
	forks[0] = p->id -1;
	forks[1] = p->id;
	if (p->id == 0){
		printf("philo number: %i\n\
	left fork id: %i\t  right fork id: %i\
		\nleft address: %p\tright address: %p\n",\
		 p->id, forks[0], forks[1], (void *)&args()->forks[args()->nb_philo - 1], (void *)&args()->forks[p->id]);
	}
	else
		printf("philo number: %i\n\
	left fork id: %i\t  right fork id: %i\
		\nleft address: %p\tright address: %p\n",\
		 p->id, forks[0], forks[1], (void *)&args()->forks[p->id -1], (void *)&args()->forks[p->id]);
}

bool	get_forks(t_philo *p)
{
	if (DEBUG)//to remove
		print_fork_assignment(p);//to remove
	if (check_stop())
		return (false);
	if (p->id == 0)
	{
		pthread_mutex_lock(&args()->forks[args()->nb_philo - 1]);
		pthread_mutex_lock(&args()->forks[p->id]);
	}
	else
	{
		pthread_mutex_lock(&args()->forks[p->id]);
		pthread_mutex_lock(&args()->forks[p->id - 1]);
	}
	if(check_stop())
	{
		drop_forks(p);
		return (false);
	}
	pthread_mutex_lock(&args()->prio);
	if (!check_stop())
	{
		printf("%ld %d has grabbed a fork\n", time_now(), p->id);
		printf("%ld %d has grabbed a fork\n", time_now(), p->id);
	}
	pthread_mutex_unlock(&args()->prio);
	return (true);
}

void	drop_forks(t_philo *p)
{
	if (p->id == 0)
	{
		pthread_mutex_unlock(&args()->forks[p->id]);
		pthread_mutex_unlock(&args()->forks[args()->nb_philo - 1]);
	}
	else
	{
		pthread_mutex_unlock(&args()->forks[p->id - 1]);
		pthread_mutex_unlock(&args()->forks[p->id]);
	}
}