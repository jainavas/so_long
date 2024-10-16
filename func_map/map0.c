/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:00:43 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/12 20:11:04 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	setto0var(t_map *vmap)
{
	vmap->nump = 0;
	vmap->pospy = 0;
	vmap->pospx = 0;
	vmap->nume = 0;
	vmap->numc = 0;
	vmap->nummoves = -1;
}

static int	maptodstr2(t_map *vmap, char *filename, int fd, int nred)
{
	char	*line;
	int		ct;
	int		width;

	fd = open(filename, O_RDONLY);
	ct = 0;
	line = get_next_line(fd);
	while (line)
	{
		vmap->map[ct] = line;
		vmap->mapcpy[ct] = ft_strdup(vmap->map[ct]);
		line = get_next_line(fd);
		ct++;
	}
	vmap->map[ct] = 0;
	vmap->mapcpy[ct] = 0;
	close(fd);
	width = ft_strlen(vmap->map[--ct]) + 1;
	while (--ct >= 0)
		if (width != (int)ft_strlen(vmap->map[ct]))
			return (ft_putstr_fd("error len lineas\n", 1), 1);
	vmap->numwd = width - 2;
	vmap->numlines = nred;
	searchcs(vmap, vmap->map);
	return (searchpe(vmap, vmap->map), 0);
}

static int	maptodstr(int numargs, char *filename, t_map *vmap)
{
	char	*temp;
	int		nred;
	int		fd;

	nred = 0;
	if (numargs != 2)
		return (ft_putstr_fd("Num de argumentos incorrecto\n", 1), 1);
	if (ft_strnstr(filename, ".ber", ft_strlen(filename)) == NULL)
		return (ft_putstr_fd("Tipo de archivo incorrecto\n", 1), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Fallo al abrir el archivo\n", 1), 1);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		free(temp);
		temp = get_next_line(fd);
		nred++;
	}
	free(temp);
	close(fd);
	vmap->map = ft_calloc(nred + 1, sizeof(char *));
	vmap->mapcpy = ft_calloc(nred + 1, sizeof(char *));
	return (setto0var(vmap), maptodstr2(vmap, filename, 0, nred));
}

static int	checkmap(t_map *vmap)
{
	int		i;
	int		j;

	i = 0;
	while (i < vmap->numlines)
	{
		j = 0;
		vmap->nump += ft_strcount(vmap->map[i], 'P');
		vmap->nume += ft_strcount(vmap->map[i], 'E');
		vmap->numc += ft_strcount(vmap->map[i], 'C');
		while (vmap->map[i][j] && (vmap->map[i][j] == 'P'
				|| vmap->map[i][j] == 'E'
				|| vmap->map[i][j] == 'C' || vmap->map[i][j] == '0'
				|| vmap->map[i][j] == '1' || vmap->map[i][j] == 10))
			j++;
		if (vmap->map[i++][j] != '\0')
			return (ft_putstr_fd("Char no permitido detectado\n", 1), 1);
	}
	if (vmap->nump != 1)
		return (ft_putstr_fd("Num de pos iniciales incorrecto\n", 1), 2);
	if (vmap->nume != 1)
		return (ft_putstr_fd("Num de salidas incorrecto\n", 1), 3);
	if (vmap->numc < 1)
		return (ft_putstr_fd("Ningun colecc encontrado\n", 1), 4);
	return (checkborder(vmap));
}

int	fullmap(mlx_type *mlxv, int numargs, char *filename)
{
	mlxv->vmap = ft_calloc(1, sizeof(t_map));
	if (mlxv->vmap == NULL)
		ft_putstr_fd("ERROR reservar mem\n", 1);
	if (maptodstr(numargs, filename, mlxv->vmap) != 0)
	{
		protectdoublestr(mlxv->vmap->map);
		protectdoublestr(mlxv->vmap->mapcpy);
		free(mlxv->vmap);
		return (ft_putstr_fd("ERROR\n", 1), 1);
	}
	if (checkmap(mlxv->vmap) != 0)
	{
		protectdoublestr(mlxv->vmap->map);
		protectdoublestr(mlxv->vmap->mapcpy);
		free(mlxv->vmap);
		return (ft_putstr_fd("ERROR check\n", 1), 1);
	}
	return (0);
}
