/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipes.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/03 08:47:17 by nherbal		   #+#	#+#			 */
/*   Updated: 2024/07/16 17:17:42 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

// int	check_pipe(char *tmp)
// {
// 	int	i;

// 	i = 0;
// 	while (tmp[i])
// 	{
// 		if (tmp[i] == '|')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

char	*get_full_path(char *cmd)
{
	char	*path_env;
	char	*path;
	char	*token;
	char	full_path[1024];

	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path = strdup(path_env);
	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

void	get_cmds_tab(char **tmp, char **cmd1, char **cmd2)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (tmp[i])
	{
		if (strcmp(tmp[i], "|") == 0)
			break ;
		cmd1[i] = strdup(tmp[i]);
		i++;
	}
	cmd1[i] = NULL;
	i++;
	while (tmp[i + j])
	{
		cmd2[j] = strdup(tmp[i + j]);
		j++;
	}
	cmd2[j] = NULL;
}

int	parse_input(char *line, char **args)
{
	int		i;
	char	*token;

	token = strtok(line, " \t\n");
	i = 0;
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;
	return (i);
}

void	execute_command(char **args, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_full_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, args, data->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	pipe_handling(t_data *data)
{
	pid_t		pid;
	int			i;
	char		**tmp;
	int			num_args;

	tmp = create_tab(data);
	num_args = parse_input(get_curr_cmd(data), tmp);
	data->num_commands = create_pipe_tab(tmp, num_args, data->pipe_indices);
	rm_tmp_quotes(tmp);
	data->pipefd = malloc(sizeof(int) * (2 * (data->num_commands - 1)));
	create_pipes(data->num_commands, data->pipefd);
	i = 0;
	while (i < data->num_commands)
	{
		pid = fork();
		do_pipe(pid, data, tmp, i);
		i++;
	}
	close_and_wait(data);
}
