/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sinawara <sinawara@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:06:43 by sinawara          #+#    #+#             */
/*   Updated: 2025/03/27 11:07:00 by sinawara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void free_map_array(char **map, int height) {
    if (map) {
        for (int i = 0; i < height; i++) {
            free(map[i]);
        }
        free(map);
    }
}