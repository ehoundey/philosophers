/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehoundey <ehoundey@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:40:21 by ehoundey          #+#    #+#             */
/*   Updated: 2022/06/11 14:37:51 by ehoundey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*функция определния времени*/

unsigned long long int	runtime_to_ms(void)
{
	unsigned long long int			ms;
	static unsigned long long int	start = 0;
	static struct timeval			time;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;
	if (!start)
		start = ms;
	return (ms - start);
}
/*фришим память*/

void	free_all(t_philo *head)
{
	t_philo	*next;

	next = head;
	free(head);
	head = head->next;
	while (next != head && head != NULL)
	{
		free(head);
		head = head->next;
	}
}
/*Функция накормить всех философов*/

int	is_all_eat(t_philo *head)
{
	t_philo	*round;

	round = head -> next;
	while (round != head)
	{
		if (round -> number_of_times_each_philosopher_must_eat > 0)
			return (0);
		round = round -> next;
	}
	return (1);
}
/*функция жизни философов*/

void	*health_center(void *void_arg)
{
	t_philo	*philo;

	philo = (t_philo *) void_arg;
	while (1)
	{
		if (philo -> number_of_times_each_philosopher_must_eat
			== 0 && is_all_eat(philo))
			return (NULL);
		if (philo -> last_eat + philo -> time_to_die + 5 < runtime_to_ms())
		{
			pthread(philo -> nth, DEAD);
			return (NULL);
		}
		philo = philo -> next;
	}
}
/*идентификатор ошибок аргументов*/

int	args_checker(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 6)
		return (write(STDERR_FILENO, "Error:\nToo many args\n", 21));
	if (ac < 5)
		return (write(STDERR_FILENO, "Error:\nArguments needed\n", 24));
	while (i < ac)
		if (ft_atoi(av[i++]) <= 0)
			return (write(STDERR_FILENO, "Error:\nA non-valid argument\n", 28));
	return (0);
}
