/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:35:09 by fabou-za          #+#    #+#             */
/*   Updated: 2023/03/02 21:45:00 by fabou-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		len;
	int		pos;
	int		pos1;
	int		i;

	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	pos = i;
	len = (int) ft_strlen(s1);
	i = len - 1;
	while (i >= 0 && ft_strchr(set, s1[i]))
		i--;
	pos1 = i;
	len = pos1 - pos + 1;
	ptr = ft_substr(s1, pos, len);
	return (ptr);
}
