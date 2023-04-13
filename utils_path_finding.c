/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merlinbourgeois <merlinbourgeois@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:05:19 by mebourge          #+#    #+#             */
/*   Updated: 2023/04/08 18:35:10 by merlinbourg      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd < 0 || !s)
		return ;
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (dst == NULL)
		return (dst);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

t_path_return *list_to_arrays(t_map_corr* head)
{
	t_path_return *coord;
	t_map_corr *copy = head;
	int nb_co;
	int i;

	nb_co = 0;
	i = 0;
	coord = malloc(1 * sizeof(t_path_return));
	while (copy != NULL )
	{
		nb_co++;
		copy = copy->next;
	}
	coord->x = malloc(nb_co * sizeof(int));
	coord->y= malloc(nb_co * sizeof(int));
	coord->moves = nb_co;
	copy = head;
	while (copy != NULL)
	{
		coord->x[i] = copy->x;
		coord->y[i] = copy->y;
		copy = copy->next;
		i++;
	}
	return(coord);
}

char **copyStrings(char** src, int numStrings) 
{
	char	**dest;
	dest = malloc(numStrings * sizeof(char *));
    for (int i = 0; i < numStrings; i++)
	{
		dest[i] = ft_strdup(src[i]);
		//printf("dest i : %s\n", dest[i]);
    }
	return (dest);
}

void printList(t_map_corr* head)
{
   	t_map_corr* current = head;
    while (current)
	{
        printf("x : %d\n", current->x);
		printf("y : %d\n", current->y);
		printf("\n");
        current = current->next;
    }
    printf("\n");
}