/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intputnbr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:47:47 by jainavas          #+#    #+#             */
/*   Updated: 2024/08/13 17:47:47 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	print_number2(unsigned int unr, char *base, int fd, int numw)
{
	char	buffer[33];
	int		i;

	i = 0;
	while (unr > 0)
	{
		buffer[i] = base[unr % 10];
		unr /= 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		numw += ft_intputchar_fd(buffer[i], fd);
		i--;
	}
	return (numw);
}

int	ft_intputnbr_fd(int n, int fd)
{
	unsigned int	un;
	int				numw;

	numw = 0;
	if (n < 0)
	{
		numw = ft_intputchar_fd('-', fd);
		un = -n;
	}
	else
		un = n;
	if (n == 0)
	{
		numw = ft_intputchar_fd('0', 1);
		return (numw);
	}
	else
	{
		numw = print_number2(un, "0123456789", fd, numw);
		return (numw);
	}
}
// int main(){
// 	ft_putnr_fd(2453,1);
// }