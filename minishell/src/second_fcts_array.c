/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_fcts_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nherbal <nherbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:24:38 by nherbal           #+#    #+#             */
/*   Updated: 2024/07/19 11:25:33 by nherbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	for_dquotes(char *tmp, t_data *data)
{
	if (tmp != NULL && check_dquotes(tmp) == 0 && data->p == -1)
	{
		data->p = 1;
		if (only_dquotes(tmp) == 1)
			built_in(data);
		else
			dquotes_built_in(data);
		free(tmp);
	}
}

void	for_squotes(char *tmp, t_data *data)
{
	if (tmp != NULL && check_squotes(tmp) == 0 && data->p == -1)
	{
		data->p = 1;
		if (only_squotes(tmp) == 1)
			built_in(data);
		else
			squotes_built_in(data);
		free(tmp);
	}
}
