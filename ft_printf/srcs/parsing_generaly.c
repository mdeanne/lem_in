/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:01:36 by mdeanne           #+#    #+#             */
/*   Updated: 2019/12/05 23:01:40 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ptintf.h"

void	parsing_cyclone(char **format, t_prsng *tools)
{
	while (**format && (is_flag(**format) || **format == '*'))
	{
		if (is_signflag(**format))
			parsing_flags(format, tools);
		else if (((**format >= '1' && **format <= '9') || **format == '*')
				&& *(*format - 1) != '.')
			parsing_field(format, tools);
		else if (**format == '.')
			parsing_precision(format, tools);
		else if (is_modifiers(**format))
			parsing_modifiers(format, tools);
		else if (is_typeflag(**format))
		{
			parsing_typeflag(format, tools);
			break ;
		}
	}
}

int		parsing(char **format, t_prsng *tools)
{
	zeroing_tools(tools, 0);
	parsing_cyclone(format, tools);
	if (!tools->type && **format)
		tools->type = *((*format)++);
	if (tools->prec < 0)
	{
		tools->flags |= M_PRECISION_NOT_ADDED;
		tools->prec = 0;
	}
	if (!(tools->flags & M_PRECISION_NOT_ADDED) &&
		tools->flags & M_ZERO && is_ddioouuxx(tools->type))
		tools->flags &= ~M_ZERO;
	return (0);
}
