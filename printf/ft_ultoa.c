/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jainavas <jainavas@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:25:30 by jainavas          #+#    #+#             */
/*   Updated: 2024/08/13 15:25:30 by jainavas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static size_t	get_digits(unsigned long n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_ultoa(unsigned long n)
{
	char			*str_num;
	size_t			digits;
	unsigned long	num;

	num = n;
	digits = get_digits(n);
	str_num = (char *)malloc(sizeof(char) * (digits + 1));
	if (str_num == NULL)
		return (NULL);
	*(str_num + digits) = 0;
	while (digits--)
	{
		*(str_num + digits) = num % 10 + '0';
		num = num / 10;
	}
	return (str_num);
}

// #include <stdio.h>
// int	main(){
// 	unsigned long i = LONG_MAX;
// 	printf("%s", ft_ultoa(i));
// }
