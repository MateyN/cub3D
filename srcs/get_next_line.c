/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:13:45 by mnikolov          #+#    #+#             */
/*   Updated: 2023/04/13 10:11:55 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_line(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, s, i + 1);
	line[i] = '\0';
	return (line);
}

char	*get_remine(char *s)
{
	char	*rest;
	int		i;
	int		s_len;

	i = 0;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	s_len = ft_strlen(&s[i]) + 1;
	rest = (char *)malloc(sizeof(char) * s_len);
	ft_strlcpy(rest, s + i, s_len);
	free(s);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*str[2];
	int			nobr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[0] = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str[0])
		return (NULL);
	nobr = 1;
	while (!ft_strchr(saved, '\n') && nobr != 0)
	{
		nobr = read(fd, str[0], BUFFER_SIZE);
		if (nobr == -1)
		{
			free(str[0]);
			return (NULL);
		}
		str[0][nobr] = 0;
		saved = ft_strjoin(saved, str[0]);
	}
	str[1] = get_line(saved);
	saved = get_remine(saved);
	free(str[0]);
	return (str[1]);
}
