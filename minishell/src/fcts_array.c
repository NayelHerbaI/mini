/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nherbal <nherbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:17:51 by nherbal           #+#    #+#             */
/*   Updated: 2024/07/19 17:32:09 by nherbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	for_pipes(char *tmp, t_data *data)
{
	if (tmp != NULL && check_pipe(tmp) == 0
		&& check_pipes_redirections_quotes(tmp) == 0 && data->p == -1)
	{
		data->p = 1;
		pipe_handling(data);
		free(tmp);
	}
}

void	for_echo_dollar(char *tmp, t_data *data)
{
	if (tmp != NULL && check_dquotes(tmp) == 0
		&& check_squotes(tmp) == 0 && data->p == -1)
	{
		data->p = 1;
		check_spec_echo(tmp, data->env);
		free(tmp);
	}
}

void	for_something(char *tmp, t_data *data)
{
	if (tmp != NULL && check_squotes(tmp) == 0
		&& check_dollar(tmp) == 0 && data->p == -1)
	{
		data->p = 1;
		check_spec_echo(tmp, data->env);
		free(tmp);
	}
}

void	for_redirections(char *tmp, t_data *data)
{
	if (tmp != NULL && check_redirection(tmp) == 1
		&& check_pipes_redirections_quotes(tmp) == 0 && data->p == -1)
	{
		data->p = 1;
		parse_command(tmp, data->dir_tab, data);
		execute_redircommand(data->dir_tab, data);
		free(tmp);
	}
}

void	for_regular_commands(char *tmp, t_data *data)
{
	if (tmp != NULL && check_dquotes(tmp) == 1
		&& check_squotes(tmp) == 1 && data->p == -1)
	{
		data->p = 1;
		built_in(data);
		free(tmp);
	}
}
