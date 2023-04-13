/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:32:11 by mebourge          #+#    #+#             */
/*   Updated: 2022/10/14 13:49:36 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned long	i;
	int				j;

	i = 0;
	while (i < n)
	{
		j = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (j)
			return (j);
			i++;
	}
	return (0);
}
