/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acalmaz <acalmaz@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:32:22 by acalmaz           #+#    #+#             */
/*   Updated: 2023/07/20 22:06:09 by acalmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	player_control(t_game *general)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	general->map->plyr_count = 0;
	while (general->map->mappin[++i])
	{
		while (general->map->mappin[i][++j])
		{
			if (general->map->mappin[i][j] == 'P')
			{
				general->map->plyr_count += 1;
			}
		}
		j = -1;
	}
	if (general->map->plyr_count != 1)
	{
		write(1, "There Should Be Only One Player\n", 33);
		close_frame(general);
	}
}

void	map_size_control(t_game *general)
{
	int	i;
	int	len;

	i = 0;
	len = general->map->width;
	while (general->map->mappin[i])
	{
		if (str_len(general->map->mappin[i]) != len)
		{
			write(1, "Line Lengths Not Equal\n", 24);
			close_frame(general);
		}
		i++;
	}
}

void	frame_control(t_game *general)
{
	int	i;
	int	end;

	i = -1;
	while (general->map->mappin[0][++i])
	{
		if (general->map->mappin[0][i] != '1' ||
			general->map->mappin[general->map->height - 1][i] != '1')
		{
			write(1, "Map Not Covered With Frame\n", 28);
			close_frame(general);
		}
	}
	i = -1;
	end = general->map->width -1;
	while (general->map->mappin[++i])
	{
		if (general->map->mappin[i][0] != '1'
			|| general->map->mappin[i][end] != '1')
		{
			write(1, "Map Not Covered With Frame\n", 28);
			close_frame(general);
		}
	}
}

void	black_hole_control(t_game *general)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (general->map->mappin[++i])
	{
		while (general->map->mappin[i][++j])
		{
			if (general->map->mappin[i][j] == 'E')
				general->map->b_h_count++;
		}
		j = 0;
	}
	if (general->map->b_h_count != 1)
	{
		write(1, "There should be only one exit cell\n", 36);
		close_frame(general);
	}
}
