/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:10:56 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/27 11:36:36 by mnikolov         ###   ########.fr       */
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

char	**add_map(char **strs, char *arg)
{
	char	**args;
	int		wlen;
	int		i;

	if (!strs[0] || !strs)
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(arg);
		args[1] = NULL;
		ft_free_ptr(strs);
		return (args);
	}
	wlen = check_args(strs);
	args = (char **)malloc(sizeof(char *) * (wlen + 1));
	i = -1;
	while (strs[++i])
		args[i] = ft_strdup(strs[i]);
	args[i] = ft_strdup(arg);
	args[i + 1] = NULL;
	ft_free_ptr(strs);
	return (args);
}
