/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:46:54 by merlinbourg       #+#    #+#             */
/*   Updated: 2023/03/12 16:11:02 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//fonction d'affichage des erreur

void	ft_error(char *str)
{
	printf("%s\n", "Error");
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}
