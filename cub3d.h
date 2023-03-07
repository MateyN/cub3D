/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:02:37 by mnikolov          #+#    #+#             */
/*   Updated: 2023/03/07 12:06:56 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <math.h>

typedef struct	s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    void	*img_ptr;
    int		*img_data;
    int		bits_per_pixel;
    int		size_line;
    int		endian;
}				t_data;

#endif