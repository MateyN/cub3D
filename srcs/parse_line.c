/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:11:11 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/04 10:49:27 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_text_name(char *element)
{
	if (!ft_strncmp(element, "NO", 3))
		return (NO);
	else if (!ft_strncmp(element, "SO", 3))
		return (SO);
	else if (!ft_strncmp(element, "WE", 3))
		return (WE);
	else if (!ft_strncmp(element, "EA", 3))
		return (EA);
	else if (!ft_strncmp(element, "F", 2))
		return (F);
	else if (!ft_strncmp(element, "C", 2))
		return (C);
	else
		return (ERROR);
}

int	get_color(char *line, int *i)
{
	int		j;
	char	*rgb;
	int		color;
	int		idx;

	if (line[*i] == ',')
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	j = *i;
	while (line[*i] && line[*i] != ',' && line[*i] != ' ')
		(*i)++;
	rgb = ft_substr(line, j, *i - j);
	idx = -1;
	while (rgb[++idx])
		if (!ft_isdigit(rgb[idx]))
			exit_error("Error: color", line);
	if (!rgb[0])
		(free(rgb), exit_error("Error: color", line));
	color = ft_atoi(rgb);
	free(rgb);
	if (color < 0 || color > 255)
		exit_error("Error: color out of range", line);
	return (color);
}

void	color_parsing(t_game *game, char *line, int element, int i)
{
	int	color[3];
	int	n;

	n = -1;
	while (++n < 3)
	{
		ft_isspaces(line, &i);
		color[n] = get_color(line, &i);
	}
	if (line[i])
		exit_error("Error: color", line);
	check_length(line);
	if (element == F && game->map->floor == -1)
		game->map->floor = (color[0] << 16) + (color[1] << 8) + color[2];
	else if (element == C && game->map->ceiling == -1)
		game->map->ceiling = (color[0] << 16) + (color[1] << 8) + color[2];
	else
		check_duplicate_color(game, element, line);
	free(line);
}

void	texture_parsing(t_game *game, char *line, int element, int i)
{
	char	*path;

	ft_isspaces(line, &i);
	path = ft_strdup(&line[i]);
	file_checker(path, ".xpm\0");
	if (element == NO && !game->map->no)
		game->map->no = path;
	else if (element == SO && !game->map->so)
		game->map->so = path;
	else if (element == WE && !game->map->we)
		game->map->we = path;
	else if (element == EA && !game->map->ea)
		game->map->ea = path;
	else
		exit_error("Error: duplicate texture", line);
	free(line);
}

int	line_parsing(t_game *game, char *line)
{
	int		i;
	int		j;
	int		element;
	char	*name;

	i = 0;
	if (is_map(line))
		return (1);
	ft_isspaces(line, &i);
	j = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	name = ft_substr(line, j, i - j);
	element = check_text_name(name);
	if (element == ERROR)
		exit_error("Error: color", name);
	else if (element == F || element == C)
		color_parsing(game, ft_strtrim(line, "\n"), element, i);
	else
		texture_parsing(game, ft_strtrim(line, "\n"), element, i);
	free(name);
	return (0);
}
