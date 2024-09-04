/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngordobi <ngordobi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:10:17 by ngordobi          #+#    #+#             */
/*   Updated: 2024/09/04 12:07:32 by ngordobi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if ((argc != 5 && argc != 6) || init(&info, argv) != 0)
	{
		printf ("Error initializing\n");
		return (-1);
	}
	printf("debug\n");
	return (0);
}
