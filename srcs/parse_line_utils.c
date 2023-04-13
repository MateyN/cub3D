/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:17 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/13 11:16:33 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	player_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	set_lines(t_game *game)
{
    if (game->map->floor == -1 || game->map->ceiling == -1
            || game->map->no == NULL || game->map->so == NULL
            || game->map->we == NULL || game->map->ea == NULL)
		exit_str("Error: Invalid file");
	return (0);
}

void	check_lenght(char *line)
{
	int		i;
	char	**f;

	i = 0;
	f = ft_split(line, ',');
	if (!f)
		exit_str("Error");
	while (f[i])
		i++;
	if (i != 3)
		exit_error("Error: Invalid color", line);
	ft_free_ptr(f);
}
