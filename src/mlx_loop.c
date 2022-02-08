/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:22:09 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/01/19 09:22:12 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(void *vars)
{
	if (++((t_vars *)vars)->frame >= 60)
		((t_vars *)vars)->frame = 0;
	handle_keys((t_vars *)vars);
	draw((t_vars *)vars);
	return (0);
}
