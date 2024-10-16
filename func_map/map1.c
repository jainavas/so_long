/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:30:36 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/11 19:10:45 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	map_floodfill_path(t_map *vmap, int y, int x)
{
	if (!vmap->mapcpy[y][x] || vmap->mapcpy[y][x] == '1'
		|| vmap->mapcpy[y][x] == 'X')
		return ;
	vmap->mapcpy[y][x] = 'X';
	map_floodfill_path(vmap, y, x + 1);
	map_floodfill_path(vmap, y + 1, x);
	map_floodfill_path(vmap, y, x - 1);
	map_floodfill_path(vmap, y - 1, x);
}

int	searchcs(t_map *vmap, char **map)
{
	char	*posi;
	int		i;
	int		j;
	int		num;

	i = 0;
	j = 0;
	num = 0;
	while (i < vmap->numlines)
	{
		posi = map[i];
		while (posi)
		{
			posi = ft_strchr(posi, 'C');
			if (posi)
			{
				num++;
				posi++;
			}
		}
		i++;
	}
	return (num);
}

int	searchpe(t_map *vmap, char **map)
{
	char	*posi;
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (i < vmap->numlines)
	{
		posi = ft_strchr(map[i], 'P');
		if (posi != NULL)
		{
			vmap->pospx = posi - map[i];
			vmap->pospy = i;
			res++;
		}
		posi = ft_strchr(map[i], 'E');
		if (posi != NULL)
		{
			vmap->posex = posi - map[i];
			vmap->posey = i;
			res++;
		}
		i++;
	}
	return (res);
}

static int	checkpossible(t_map *vmap)
{
	map_floodfill_path(vmap, vmap->pospy, vmap->pospx);
	if (searchcs(vmap, vmap->mapcpy) != 0)
		return (ft_putstr_fd("Algun c inaccesible\n", 1), 1);
	if (searchpe(vmap, vmap->mapcpy) != 0)
		return (ft_putstr_fd("Algun e inaccesible\n", 1), 1);
	protectdoublestr(vmap->mapcpy);
	return (0);
}

int	checkborder(t_map *vmap)
{
	int	i;

	i = 0;
	if (ft_strcount(vmap->map[0], '1') != vmap->numwd + 1)
		return (ft_putstr_fd("borde superior mal\n", 1), 1);
	while (i < vmap->numlines)
	{
		if (vmap->map[i][0] != '1' || vmap->map[i++][vmap->numwd] != '1')
			return (ft_putstr_fd("borde lateral mal\n", 1), 1);
	}
	if (ft_strcount(vmap->map[i - 1], '1') != vmap->numwd + 1)
		return (ft_putstr_fd("borde inferior mal\n", 1), 1);
	return (checkpossible(vmap));
}
