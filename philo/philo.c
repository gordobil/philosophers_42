/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/06 10:22:48 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo(t_info info)
{

}

int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || init(&info, argv) != 0)
	{
		printf ("Error initializing\n");
		return (-1);
	}
	if (philo(info) != 0)
	{
		printf ("Error\n");
		return (-1);
	}
	return (0);
}
