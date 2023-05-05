/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:10:56 by mnikolov          #+#    #+#             */
/*   Updated: 2023/05/05 10:35:38 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_isspaces(char *s, int *i)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
}

int	is_map(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' '
			&& line[i] != '\n')
			return (0);
	}
	return (1);
}

int	check_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 1;
	while (args[i++])
		;
	return (i);
}

char	**add_map(char **arr, char *arg)
{
	char	**new_arr;
	int		arr_length;
	int		i;

	if (arr[0] == NULL || arr == NULL)
	{
		new_arr = (char **)malloc(sizeof(char *) * 2);
		new_arr[0] = ft_strdup(arg);
		new_arr[1] = NULL;
		ft_free_ptr(arr);
		return (new_arr);
	}
	arr_length = check_args(arr);
	new_arr = (char **)malloc(sizeof(char *) * (arr_length + 1));
	i = 0;
	while (arr[i] != NULL)
	{
    	new_arr[i] = ft_strdup(arr[i]);
    	i++;
	}
	new_arr[i] = ft_strdup(arg);
	new_arr[i + 1] = NULL;
	ft_free_ptr(arr);
	return (new_arr);
}
