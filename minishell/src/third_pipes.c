/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   third_pipes.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: naherbal <naherbal@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/17 14:49:06 by naherbal		  #+#	#+#			 */
/*   Updated: 2024/07/17 15:39:14 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipe(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '|')
			return (0);
		i++;
	}
	return (1);
}

void	close_and_wait(t_data *data)
{
	int	i;

	i = 0;
	while (i < 2 * (data->num_commands - 1))
	{
		close(data->pipefd[i]);
		i++;
	}
	i = 0;
	while (i < data->num_commands)
	{
		wait(NULL);
		i++;
	}
}

void	execute_cmds(char **tmp, t_data *data, int *pipe_indices, int i)
{
	if (i == 0)
		execute_command(tmp, data);
	else
		execute_command(tmp + pipe_indices[i - 1] + 1, data);
}

void	second_do_pipe(t_data *data, int i)
{
	int	j;

	if (i != data->num_commands - 1)
	{
		if (dup2(data->pipefd[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	j = 0;
	while (j < 2 * (data->num_commands - 1))
	{
		close(data->pipefd[j]);
		j++;
	}
}

void	do_pipe(int pid, t_data *data, char **tmp, int i)
{
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (i != 0)
		{
			if (dup2(data->pipefd[(i - 1) * 2], STDIN_FILENO) == -1)
			{
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		second_do_pipe(data, i);
		execute_cmds(tmp, data, data->pipe_indices, i);
	}
}
