/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:10:34 by jainavas          #+#    #+#             */
/*   Updated: 2024/10/02 01:35:05 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = 0;
	while (src[s])
		s++;
	if (!dstsize)
		return (s);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (s);
}

static char	*ft_truncstr(char *ogs)
{
	char	*str;
	char	len;

	str = NULL;
	if (ft_strlen(ogs) > 9)
	{
		str = malloc(sizeof(char) * 9);
		len = ft_strlen(ogs) - 8;
		ft_strlcpy(str, (ogs + len), 9);
		free(ogs);
		return (str);
	}
	return (ogs);
}

static char	*print_long(char *buffer, unsigned long unbr, char *base)
{
	unsigned int	i;
	char			temp;

	i = 0;
	if (unbr == 0)
	{
		buffer[0] = base[0];
		buffer[1] = '\0';
		return (buffer);
	}
	while (unbr > 0)
	{
		buffer[i++] = base[unbr % 16];
		unbr /= 16;
	}
	buffer[i] = '\0';
	i = 0;
	while (i < ft_strlen(buffer) / 2)
	{
		temp = buffer[i];
		buffer[i] = buffer[ft_strlen(buffer) - 1 - i];
		buffer[ft_strlen(buffer) - 1 - i] = temp;
		i++;
	}
	return (buffer);
}

char	*ft_putlong_base(unsigned long lnbr, char *base)
{
	char	*buffer;
	char	*tmp;
	long	nbr;

	if (lnbr == ULONG_MAX || lnbr == LONG_MAX)
		nbr = 4294967295;
	else
	{
		if (lnbr == 9223372036854775808ULL)
			nbr = 0;
		else
			nbr = lnbr;
	}
	tmp = malloc(sizeof(char) * 30);
	tmp = print_long(tmp, nbr, base);
	buffer = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!buffer)
		return ((void *)0);
	ft_strlcpy(buffer, tmp, (ft_strlen(tmp) + 1));
	free(tmp);
	return (ft_truncstr(buffer));
}
