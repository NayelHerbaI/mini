/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   history_creation.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/12 18:28:37 by marvin			#+#	#+#			 */
/*   Updated: 2024/07/16 17:28:24 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	only_dquotes(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i + 1])
	{
		if (tmp[i] == '\"' && tmp[i + 1] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	only_squotes(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i + 1])
	{
		if (tmp[i] == '\'' && tmp[i + 1] == '\'')
			return (1);
		i++;
	}
	return (0);
}

void	second_first_node_creation(t_data *data, char *tmp)
{
	data->history->prompt_command = strdup(tmp);
	data->history->cmds_tab = ft_split(tmp, ' ');
	if (check_dquotes(tmp) == 0)
	{
		if (only_dquotes(tmp) == 0)
			data->history->dq_cmd = remove_dquotes(tmp);
		data->history->dquotes_tab = ft_split(data->history->dq_cmd, ' ');
	}
	if (check_squotes(tmp) == 0)
	{
		data->history->sq_cmd = remove_squotes(tmp);
		data->history->squote_tab = ft_split(data->history->sq_cmd, ' ');
	}
	if (check_pipe(tmp) == 0)
	{
		data->history->pipe_tab = ft_split(tmp, ' ');
	}
}

void	first_node_creation(t_data *data, char *tmp)
{
	data->history = malloc(sizeof(t_commands));
	data->history->dq_cmd = NULL;
	data->history->dquotes_tab = NULL;
	data->history->squote_tab = NULL;
	data->history->sq_cmd = NULL;
	data->history->dq_cmd = NULL;
	data->history->pipe_tab = 0;
	data->history->tokens = NULL;
	if (!tmp || strcmp(tmp, "\n") == 0)
	{
		data->history->prompt_command = NULL;
		data->history->cmds_tab = NULL;
		data->history->dq_cmd = NULL;
		data->history->dquotes_tab = NULL;
		data->history->sq_cmd = NULL;
		data->history->squote_tab = NULL;
	}
	else
		second_first_node_creation(data, tmp);
	data->history->next = NULL;
	data->first_node = 1;
}

void	create_last_node(t_data *data, char *tmp)
{
	t_commands	*new;
	t_commands	*curr;

	new = malloc(sizeof(t_commands));
	new->dq_cmd = NULL;
	new->sq_cmd = NULL;
	new->dquotes_tab = NULL;
	new->squote_tab = NULL;
	new->pipe_tab = 0;
	new->tokens = NULL;
	if (!tmp || strcmp(tmp, "\n") == 0)
		for_null(new);
	else
		for_fill_new(new, tmp);
	new->next = NULL;
	curr = data->history;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
}
