/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naherbal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:04:09 by naherbal          #+#    #+#             */
/*   Updated: 2024/07/16 20:04:18 by naherbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_data_arrays(t_data *data)
{
	free(data->dir_tab);
}

void	free_tokens(t_data *data)
{
	t_commands	*curr;
	int			i;

	curr = data->history;
	while (curr != NULL)
	{
		i = 0;
		if (curr->tokens)
		{
			while (curr->tokens[i])
				free(curr->tokens[i++]);
		}
		free(curr->tokens);
		curr = curr->next;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

void	free_string(char *str)
{
	if (str)
		free(str);
}

void	free_linked_list(t_data *data)
{
	t_commands	*curr;
	t_commands	*next;

	curr = data->history;
	while (curr != NULL)
	{
		free_arr(curr->cmds_tab);
		free_arr(curr->dquotes_tab);
		free_arr(curr->squote_tab);
		// free_arr(curr->pipe_tab);
		free_arr(curr->tokens);
		free_string(curr->prompt_command);
		free_string(curr->dq_cmd);
		free_string(curr->sq_cmd);
		next = curr->next;
		free(curr);
		curr = next;
	}
}

void	free_data(t_data *data)
{
	free_linked_list(data);
	free_data_arrays(data);
	free(data);
}
