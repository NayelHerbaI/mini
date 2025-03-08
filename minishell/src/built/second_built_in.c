/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nherbal <nherbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:49:23 by nherbal           #+#    #+#             */
/*   Updated: 2024/07/19 16:52:02 by nherbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	for_print_history(t_data *data, char **tmp)
{
	if (tmp[0] && tmp[1] && strcmp(tmp[0], "history") == 0 && data->built == -1)
	{
		print_history(data, atoi(tmp[1]));
		data->built = 1;
	}
}

void	for_print_nb_history(t_data *data, char **tmp)
{
	if (tmp[0] && strcmp(tmp[0], "history") == 0 && data->built == -1)
	{
		print_history(data, -1);
		data->built = 1;
	}
}

void	for_unset(t_data *data, char **tmp)
{
	if (tmp[0] && tmp[1] && strcmp(tmp[0], "unset") == 0 && data->built == -1)
	{
		ft_unset(data->env, tmp[1]);
		data->built = 1;
	}
}

void	for_exit(t_data *data, char **tmp)
{
	if (tmp[0] && strcmp(tmp[0], "unset") == 0 && data->built == -1)
		return ;
}

void	for_path_exec(t_data *data, char **tmp)
{
	if (tmp[0] && strcmp(tmp[0], "exit") != 0 && data->built == -1)
	{
		path_exec(data, tmp[0], &tmp[0]);
		data->built = 1;
	}
}
