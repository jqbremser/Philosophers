/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kronos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:54:00 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/02 14:09:54 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

size_t update_time(void)
{
	struct timeval time;

	if(gettimeofday(&time, NULL) == -1)
	    (void)!write(2, "Update_time failed\n", 20);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_usleep(size_t mili, t_moniter *overseer)
{
	long start;
	 
	start = update_time();
	// printf("inside usleep\n");
	while ((update_time() - start) < mili)
	{
		if (!hemlocked(overseer))
			usleep(500);
	}	
	// printf("end of usleep\n");

}