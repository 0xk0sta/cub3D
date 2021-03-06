/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprite_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostal- <acostal-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:04:02 by acostal-          #+#    #+#             */
/*   Updated: 2022/02/09 13:04:03 by acostal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_sprites(const t_map *map, char **aux, int *i, int *id)
{
	map->spaux[(*id)].id = (*id);
	map->spaux[(*id)].type = ft_strdup(aux[0]);
	(*id)++;
	(*i)++;
	free_split(aux);
}

void	alloc_sprites_struct(t_map *map)
{
	map->sprites = (char ***)ft_calloc(map->sprite_cnt + 1, sizeof(char **));
	map->spaux = (t_spaux *)ft_calloc(map->sprite_cnt + 1, sizeof(t_spaux));
}
