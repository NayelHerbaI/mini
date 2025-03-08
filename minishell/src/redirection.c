/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   redirection.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/05 00:55:48 by nherbal		   #+#	#+#			 */
/*   Updated: 2024/07/16 17:38:15 by naherbal		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_redirection(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i + 1] && ((tmp[i] == '>' || tmp[i] == '<')
				|| (tmp[i] == '>' && tmp[i + 1] == '>')
				|| (tmp[i] == '<' && tmp[i + 1] == '<')))
			return (1);
		i++;
	}
	return (0);
}

void	parse_command(char *cmd, char **args, t_data *data)
{
	char	*token;

	data->input_file = NULL;
	data->output_file = NULL;
	data->append = 0;
	data->here_document = 0;
	data->arg_count = 0;
	token = strtok(cmd, " ");
	while (token != NULL)
	{
		second_parse_command(token, data, args);
		token = strtok(NULL, " ");
	}
	args[data->arg_count] = NULL;
}

void	handle_here_document(const char *delimiter)
{
	int		pipefd[2];
	char	buffer[1024];

	pipe(pipefd);
	if (fork() == 0)
	{
		close(pipefd[0]);
		while (1)
		{
			printf("> ");
			fgets(buffer, sizeof(buffer), stdin);
			if (strncmp(buffer, delimiter, strlen(delimiter)) == 0)
				break ;
			write(pipefd[1], buffer, strlen(buffer));
		}
		close(pipefd[1]);
		exit(0);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	wait(NULL);
}

void	execute_redircommand(char **args, t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		second_execute_redircommand(data);
		third_execute_redircommand(data, args);
	}
	else if (pid > 0)
		wait(NULL);
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
