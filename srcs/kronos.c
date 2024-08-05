/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kronos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:54:00 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/03 22:31:56 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

size_t	update_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		(void)!write(2, "Update_time failed\n", 20);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t mili, t_monitor *overseer)
{
	long	start;

	start = update_time();
	while ((update_time() - start) < mili)
	{
		if (hemlocked(overseer))
			break ;
		usleep(500);
	}	
}
