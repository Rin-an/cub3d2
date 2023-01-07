/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:21:10 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/07 17:16:39 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include <stdbool.h>

char    *ft_strchr(const char *s, int c);
char    *ft_strrchr(const char *s, int c);
int    ft_strcmp(const char *s1,  const char *s);
char	**ft_split(const char *s, char c);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
void    *ft_calloc(size_t count, size_t size);
#endif
