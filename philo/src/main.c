/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufreire <gufreire@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:34:18 by gufreire          #+#    #+#             */
/*   Updated: 2025/10/26 16:05:34 by gufreire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philos.h"

int	main(int ac, char **av)
{
	if (pars(ac, av) == false)
		return (1);
	if (!innit_everything())
		return (2);
	monitor();
	while (!check_stop())
		usleep(1000);  	
	clean();
	return (0);
}