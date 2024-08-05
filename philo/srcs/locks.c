/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:48:58 by jbremser          #+#    #+#             */
/*   Updated: 2024/08/04 02:36:50 by jbremser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../symposium.h"

extern char *philosopher_names[400];

int load_philosopher_names(const char *filename, char **philosopher_names, int max_philosophers)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Failed to open philosopher names file");
        return (-1);
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < max_philosophers)
    {
        line[strcspn(line, "\n")] = 0;  // Remove the newline character
        philosopher_names[count] = strdup(line);
        if (!philosopher_names[count])
        {
            perror("Failed to allocate memory for philosopher name");
            fclose(file);
            return (-1);
        }
        count++;
    }
    fclose(file);
    return count;
}

int	print_message(const char *message, t_philo *philo)
{
	unsigned int	time;
	const char *philosopher_name;

	pthread_mutex_lock(&philo->overseer->print_lock);
	if (hemlocked(philo->overseer))
	{
		pthread_mutex_unlock(&philo->overseer->print_lock);
		return (1);
	}
	time = (update_time() - philo->overseer->symposium_start);
	philosopher_name = philosopher_names[philo->id - 1]; // Adjust index for 0-based array
	printf("%u %s %s\n", time, philosopher_name, message);
	pthread_mutex_unlock(&philo->overseer->print_lock);
	return (0);
}

void	ostracize(t_monitor *overseer)
{
	pthread_mutex_lock(&overseer->hemlock);
	overseer->hemlock_taken = true;
	pthread_mutex_unlock(&overseer->hemlock);
}

int	hemlocked(t_monitor *overseer)
{
	pthread_mutex_lock(&overseer->hemlock);
	if (overseer->hemlock_taken)
	{
		pthread_mutex_unlock(&overseer->hemlock);
		return (1);
	}
	pthread_mutex_unlock(&overseer->hemlock);
	return (0);
}
