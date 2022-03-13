/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lechalme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 21:04:58 by lechalme          #+#    #+#             */
/*   Updated: 2022/03/11 21:05:00 by lechalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	error_msg(char *str)
{
	ft_putstr_fd("Error\n", 2);
	if (errno == 0 || !ft_strcmp("Not valid map\n", str))
		ft_putstr_fd(str, 2);
	else
		perror(str);
	exit(EXIT_FAILURE);
}
