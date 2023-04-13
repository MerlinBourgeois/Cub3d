/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:52:43 by mebourge          #+#    #+#             */
/*   Updated: 2022/10/15 18:28:04 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dstcast;
	const char	*srccast;

	if (dst == src || n == 0)
		return (dst);
	if (!dst && !src)
		return (NULL);
	dstcast = (char *)dst;
	srccast = (const char *)src;
	while (n--)
		*dstcast++ = *srccast++;
	return (dst);
}
