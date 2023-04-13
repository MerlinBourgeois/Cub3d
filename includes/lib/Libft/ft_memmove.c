/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:32:46 by mebourge          #+#    #+#             */
/*   Updated: 2022/10/15 18:30:04 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*buffersrc;
	unsigned char	*bufferdst;

	buffersrc = (unsigned char *)src;
	bufferdst = (unsigned char *)dst;
	if (bufferdst < buffersrc)
		while (len--)
			*bufferdst++ = *buffersrc++;
	if (bufferdst > buffersrc)
		while (len--)
			bufferdst[len] = buffersrc[len];
	return (dst);
}
