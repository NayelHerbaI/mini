/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   path_exec.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/23 17:22:16 by marvin			#+#	#+#			 */
/*   Updated: 2024/07/16 16:29:37 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_error(char *cmd)
{
	ft_putstr_fd("-bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	second_path_exec(t_data *data, char *cmd, char **args)
{
	pid_t	pid;
	int		status;

	cmd = secure_path(data->env, cmd, data);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (access(cmd, X_OK) == 0)
			data->last_return_value = execve(cmd, args, data->env);
		else if (access(cmd, X_OK) == 0)
			data->last_return_value = execve(cmd, args, data->env);
		write_error(cmd);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->last_return_value = WEXITSTATUS(status);
	}
}

void	path_exec(t_data *data, char *cmd, char **args)
{
	if (args != NULL && strcmp(cmd, "echo") == 0 && strcmp(args[1], "$?") == 0)
	{
		ft_putnbr_fd(data->last_return_value, 1);
		ft_putchar('\n');
		data->last_return_value = 0;
		return ;
	}
	if (strcmp(secure_path(data->env, cmd, data), "PATH=") == 0)
		return (write_error(cmd));
	second_path_exec(data, cmd, args);
}
