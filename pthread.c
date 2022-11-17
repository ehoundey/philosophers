/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehoundey <ehoundey@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:12:53 by ehoundey          #+#    #+#             */
/*   Updated: 2022/06/11 14:35:11 by ehoundey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*потоки*/
void	pthread(int nth, int job)
{
	static pthread_mutex_t	p;
	static pthread_mutex_t	*pen = NULL;

	if (pen == NULL)
	{
		pen = &p;
		pthread_mutex_init(pen, NULL);
	}
	pthread_mutex_lock(pen);
	if (job == FORK)
		printf("%llu %d has taken a fork\n", runtime_to_ms(), nth);
	else if (job == EAT)
		printf("%llu %d is eating\n", runtime_to_ms(), nth);
	else if (job == SLEEP)
		printf("%llu %d is sleeping\n", runtime_to_ms(), nth);
	else if (job == THINK)
		printf("%llu %d is thinking\n", runtime_to_ms(), nth);
	else
	{
		printf("%llu %d died\n", runtime_to_ms(), nth);
		return ;
	}
	pthread_mutex_unlock(pen);
}
