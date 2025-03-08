/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nherbal <nherbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:50:30 by nherbal           #+#    #+#             */
/*   Updated: 2024/07/19 16:53:10 by nherbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	for_dollar_echo(t_data *data, char **tmp)
{
	if (tmp[0] && strcmp(tmp[0], "echo") == 0 && nb_args(tmp) == 1
		&& data->built == -1)
	{
		ft_echo(data->env, tmp);
		data->built = 1;
	}
}

void	for_pwd(t_data *data, char **tmp)
{
	if (tmp[0] && strcmp(tmp[0], "pwd") == 0 && data->built == -1)
	{
		ft_pwd();
		data->built = 1;
	}
}

void	for_export(t_data *data, char **tmp)
{
	if (tmp[0] && tmp[1] && strcmp(tmp[0], "export") == 0
		&& data->built == -1)
	{
		ft_export(data->env, tmp[1]);
		data->built = 1;
	}
}

void	for_env(t_data *data, char **tmp)
{
	if (tmp[0] && strcmp(tmp[0], "env") == 0 && data->built == -1)
	{
		ft_env(data->env);
		data->built = 1;
	}
}

void	for_cd(t_data *data, char **tmp)
{
	if (tmp[0] && strcmp(tmp[0], "cd") == 0 && data->built == -1)
	{
		ft_cd(data, tmp[1]);
		data->built = 1;
	}
}
