/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <mnikolov@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:13:45 by mnikolov          #+#    #+#             */
/*   Updated: 2021/12/09 14:06:07 by mnikolov         ###   ########.fr       */
/*                                                                            */
/**************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE	10000000
#endif

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void	ft_read_file(int fd, char **save);
char    *get_next_line(int fd);
char    *ft_strchr(const char *s, int c);
char    *ft_return_line(char **buff);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
