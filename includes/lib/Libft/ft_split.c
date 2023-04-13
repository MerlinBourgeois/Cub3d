/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:53:10 by mebourge          #+#    #+#             */
/*   Updated: 2022/10/24 14:14:36 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	char_is_in_c(char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

int	get_ac(char const *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (char_is_in_c(str[i], c))
			i++;
		if (!char_is_in_c(str[i], c) && str[i])
		{
			count++;
			while (!char_is_in_c(str[i], c) && str[i])
				i++;
		}
	}
	return (count + 1);
}

char	*get_next_word(int *index, char const *str, char c)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = 0;
	while (char_is_in_c(str[*index], c))
		(*index)++;
	while (!char_is_in_c(str[*index + len], c) && str[*index + len])
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i++] = str[*index];
		*index = *index + 1;
	}
	res[i] = 0;
	return (res);
}

void	ft_free_res(int i, char **res)
{
	while (i--)
		free(res[i]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		ac;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	ac = get_ac(s, c);
	res = malloc(ac * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < ac - 1)
	{
		res[i++] = get_next_word(&j, s, c);
		if (!res[i - 1])
		{
			ft_free_res(i, res);
			return (NULL);
		}
	}	
	res[i] = 0;
	return (res);
}
