/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_history_creation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naherbal <naherbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:15:22 by nherbal           #+#    #+#             */
/*   Updated: 2024/07/20 17:14:27 by naherbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	for_null(t_commands *new)
{
	new->prompt_command = NULL;
	new->cmds_tab = NULL;
	new->dq_cmd = NULL;
	new->dquotes_tab = NULL;
	new->sq_cmd = NULL;
	new->squote_tab = NULL;
	new->tokens = NULL;
}

void	for_fill_new(t_commands *new, char *tmp)
{
	new->prompt_command = strdup(tmp);
	new->cmds_tab = ft_split(tmp, ' ');
	new->tokens = NULL;
	new->pipe_tab = 0;
	if (check_dquotes(tmp) == 0)
	{
		new->dq_cmd = remove_dquotes(tmp);
		new->dquotes_tab = ft_split(new->dq_cmd, ' ');
	}
	if (check_squotes(tmp) == 0)
	{
		new->sq_cmd = remove_squotes(tmp);
		new->squote_tab = ft_split(new->sq_cmd, ' ');
	}
	if (check_pipe(tmp) == 0)
	{
		new->pipe_tab = ft_split(tmp, ' ');
	}
}
