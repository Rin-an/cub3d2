/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadiki <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:44 by ssadiki           #+#    #+#             */
/*   Updated: 2023/01/07 19:30:47 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line/get_next_line.h"

bool	check_identifiers(char *s, bool *exist)
{
	if (!ft_strcmp(s, "NO") && !exist[0])
		exist[0] = 1;
	else if (!ft_strcmp(s, "SO") && !exist[1])
		exist[1] = 1;
	else if (!ft_strcmp(s, "WE") && !exist[2])
		exist[2] = 1;
	else if (!ft_strcmp(s, "EA") && !exist[3])
		exist[3] = 1;
	else if (!ft_strcmp(s, "F") && !exist[4])
		exist[4] = 1;
	else if (!ft_strcmp(s, "C") && !exist[5])
		exist[5] = 1;
	else
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
//	int		i;
	char	*s;
	if (argc != 2)
		printf("Too many or few arguments!\n");
	else
	{
		if (ft_strchr(argv[1], '.') == ft_strrchr(argv[1], '.'))
		{
			char	*pt = ft_strchr(argv[1], '.');
			
			if (!pt || ft_strcmp(pt, ".cub"))
				return (printf("Error\nWrong extension!"));
		}
		else
			return (printf("Error\nWrong extension!"));
		int	fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (printf("Error\nError opening the file!"));
		char	**sp;
		bool	*exist = ft_calloc(sizeof(bool), 6);
		s = get_next_line(fd);
		while (s)
		{
			sp = ft_split(s, ' ');
			if (!sp)
				return (printf("Error\nSomething went wrong in split!"));
			if (check_identifiers(sp[0], exist) == true)
				return (printf("Error\nError in identifiers!\n"));
		s = get_next_line(fd);
		}
	}
	return (0);
}
