/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:26:59 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/04 18:27:05 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_coordinates(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == ' ')
		{
			i++;
			tmp = str + 1;
			while (*tmp && *tmp != ' ')
			{
				if (!ft_isdigit(*tmp))
					go_exit("ERROR: file contains invalid room");
				tmp++;
			}
		}
		str++;
	}
	if (i != 2)
		go_exit("ERROR: file contains invalid room");
}

int		check_room(char *line, int type, int *flag)
{
	char	*tmp;
	int		i;

	if (type == 1 || type == 2)
		return (3);
	else if (type != 3)
		go_exit("ERROR: wrong order in file");
	if (*flag == 1)
		(*flag)++;
	i = 0;
	if (*line == ' ')
		go_exit("ERROR: room name starts with ' '");
	if (*line == 'L')
		go_exit("ERROR: room name starts with 'L'");
	if ((tmp = ft_strchr(line, ' ')) < ft_strchr(line, '-'))
		go_exit("ERROR: room name contains '-'");
	check_coordinates(tmp);
	return (3);
}

int		check_link(char *line, int *flag)
{
	char *tmp;

	if (flag)
		(*flag)++;
	tmp = ft_strchr(line, '-') + 1;
	if (ft_strchr(tmp, '-'))
		go_exit("ERROR: in link room name contains '-'");
	while (*tmp && *line != '-')
	{
		if (*tmp != *line)
			break ;
		tmp++;
		line++;
	}
	if (!*tmp && *line == '-')
		go_exit("ERROR: link has identical rooms");
	return (4);
}

int		check_ants(char *line, int type)
{
	if (type != 5)
		go_exit("ERROR: wrong order in file");
	while (*line)
	{
		if (!ft_isdigit(*line))
			go_exit("ERROR: invalid ants representation");
		line++;
	}
	return (5);
}

int		check_valid_line(char *line)
{
	static int	flag;
	int			type;

	if (!(type = type_of_line(line)))
		return (flag);
	if (!flag)
	{
		check_ants(line, type);
		flag++;
	}
	else if (flag == 2 && type == 4)
		check_link(line, &flag);
	else if (flag == 1 || flag == 2)
		check_room(line, type, &flag);
	else if (flag == 3 && type != 4)
		go_exit("ERROR: wrong order in file");
	else if (flag == 3)
		check_link(line, NULL);
	else
		go_exit("ERROR: file not contains rooms");
	return (flag);
}
