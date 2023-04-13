/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 20:11:26 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/03/13 18:47:24 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//fonction de free pour les tableau de char

void	free_tab(char **tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

void	*ft_realloc(void *p, size_t size)
{
	void	*new_alloc;

	if (!p)
		return (NULL);
	new_alloc = malloc(size);
	if (!new_alloc)
		return (p);
	ft_memmove(new_alloc, p, size);
	free(p);
	return (new_alloc);
}
