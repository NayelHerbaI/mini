/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   second_redirection.c							   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: naherbal <naherbal@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/17 15:40:09 by naherbal		  #+#	#+#			 */
/*   Updated: 2024/07/17 18:21:41 by naherbal		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

void	third_execute_redircommand(t_data *data, char **args)
{
	char	*env_paths;
	char	*token;
	char	path[1024];

	if (data->here_document)
		handle_here_document(data->input_file);
	env_paths = getenv("PATH");
	token = strtok(env_paths, ":");
	while (token != NULL)
	{
		snprintf(path, sizeof(path), "%s/%s", token, args[0]);
		execve(path, args, data->env);
		token = strtok(NULL, ":");
	}
	perror("execve");
	exit(EXIT_FAILURE);
}

void	fourth_execute_redircommand(t_data *data)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (data->output_file)
	{
		if (data->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd = open(data->output_file, flags, 0644);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	second_execute_redircommand(t_data *data)
{
	int	fd;

	if (data->input_file && !data->here_document)
	{
		fd = open(data->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	fourth_execute_redircommand(data);
}

void	second_parse_command(char *token, t_data *data, char **args)
{
	if (strcmp(token, "<") == 0)
	{
		token = strtok(NULL, " ");
		data->input_file = token;
	}
	else if (strcmp(token, ">") == 0)
	{
		token = strtok(NULL, " ");
		data->output_file = token;
		data->append = 0;
	}
	else if (strcmp(token, ">>") == 0)
	{
		token = strtok(NULL, " ");
		data->output_file = token;
		data->append = 1;
	}
	else if (strcmp(token, "<<") == 0)
	{
		token = strtok(NULL, " ");
		data->here_document = 1;
		data->input_file = token;
	}
	else
		args[data->arg_count++] = token;
}
