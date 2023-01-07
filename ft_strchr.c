/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:31:45 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/07 16:21:04 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strchr(const char *s, int c)

{
	char	*p;

	p = NULL;
	while (*s != '\0')
	{
		if ((char)c == *s)
		{
			p = (char *)s;
			return (p);
		}
		s++;
	}
	if ((char)c == *s)
		p = (char *)s;
	return (p);
}
