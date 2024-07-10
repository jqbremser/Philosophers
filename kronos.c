/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kronos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:54:00 by jbremser          #+#    #+#             */
/*   Updated: 2024/07/08 17:53:34 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "symposium.h"

size_t kronosophize(void)
{
	struct timeval time;

	if(gettimeofday(&time, NULL) == -1)
		printf("Lauren's function is not working\n");
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

void ft_usleep(size_t mili)
{
	 long start;
	 

	start = kronosophize();
	while ((kronosophize() - start) < mili)
		usleep(500);
}

size_t update_krono(size_t start_time)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	return((current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - start_time);
}

