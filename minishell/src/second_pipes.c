/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   second_pipes.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: naherbal <naherbal@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/17 14:31:31 by naherbal		  #+#	#+#			 */
/*   Updated: 2024/07/17 15:38:42 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

char	**create_tab(t_data *data)
{
	t_commands	*curr;

	curr = data->history;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr->pipe_tab);
}

char	*get_curr_cmd(t_data *data)
{
	t_commands	*curr;

	curr = data->history;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr->prompt_command);
}

int	create_pipe_tab(char **tmp, int num_args, int *pipe_indices)
{
	int	o;
	int	num_commands;

	num_commands = 1;
	o = 0;
	while (o < num_args)
	{
		if (strcmp(tmp[o], "|") == 0)
		{
			pipe_indices[num_commands - 1] = o;
			tmp[o] = NULL;
			num_commands++;
		}
		o++;
	}
	return (num_commands);
}

void	rm_tmp_quotes(char **tmp)
{
	int	p;

	p = 0;
	while (tmp[p])
	{
		if (check_dquotes(tmp[p]) == 0)
			tmp[p] = remove_dquotes(tmp[p]);
		else if (check_squotes(tmp[p]) == 0)
			tmp[p] = remove_squotes(tmp[p]);
		p++;
	}
}

void	create_pipes(int num_commands, int *pipefd)
{
	int	i;

	i = 0;
	while (i < num_commands - 1)
	{
		if (pipe(pipefd + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
