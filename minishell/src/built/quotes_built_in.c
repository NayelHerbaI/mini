/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   quotes_built_in.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/27 17:58:34 by naherbal		  #+#	#+#			 */
/*   Updated: 2024/07/16 15:52:39 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_hash(char **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == '#')
				tmp[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	second_dquotes_built_in(t_data *data, char **tmp)
{
	if (tmp[0] && tmp[1] && strcmp(tmp[1], "$?") != 0
		&& strcmp(tmp[0], "echo") == 0)
		ft_echo(data->env, tmp);
	else if (tmp[0] && strcmp(tmp[0], "echo") == 0)
		ft_echo(data->env, tmp);
	else if (tmp[0] && strcmp(tmp[0], "pwd") == 0)
		ft_pwd();
	else if (tmp[0] && tmp[1] && strcmp(tmp[0], "export") == 0)
		ft_export(data->env, tmp[1]);
	else if (tmp[0] && strcmp(tmp[0], "env") == 0)
		ft_env(data->env);
	else if (tmp[0] && strcmp(tmp[0], "cd") == 0)
		ft_cd(data, tmp[1]);
	else if (tmp[0] && tmp[1] && strcmp(tmp[0], "history") == 0)
		print_history(data, atoi(tmp[1]));
	else if (tmp[0] && strcmp(tmp[0], "history") == 0)
		print_history(data, -1);
	else if (tmp[0] && tmp[1] && strcmp(tmp[0], "unset") == 0)
		ft_unset(data->env, tmp[1]);
	else if (tmp[0] && strcmp(tmp[0], "unset") == 0)
		return ;
	else if (tmp[0] && strcmp(tmp[0], "exit") != 0)
		path_exec(data, tmp[0], &tmp[0]);
}

void	dquotes_built_in(t_data *data)
{
	char		**tmp;
	t_commands	*cmd;

	cmd = data->history;
	while (cmd->next != NULL)
		cmd = cmd->next;
	tmp = cmd->dquotes_tab;
	if (tmp != NULL)
		replace_hash(tmp);
	else
	{
		path_exec(data, NULL, NULL);
		return ;
	}
	second_dquotes_built_in(data, tmp);
}

void	second_squotes_built_in(t_data *data, char **tmp)
{
	if (tmp[0] && tmp[1] && strcmp(tmp[1], "$?") != 0
		&& strcmp(tmp[0], "echo") == 0)
		ft_echo(data->env, tmp);
	else if (tmp[0] && strcmp(tmp[0], "echo") == 0)
		ft_echo(data->env, tmp);
	else if (tmp[0] && strcmp(tmp[0], "pwd") == 0)
		ft_pwd();
	else if (tmp[0] && tmp[1] && strcmp(tmp[0], "export") == 0)
		ft_export(data->env, tmp[1]);
	else if (tmp[0] && strcmp(tmp[0], "env") == 0)
		ft_env(data->env);
	else if (tmp[0] && strcmp(tmp[0], "cd") == 0)
		ft_cd(data, tmp[1]);
	else if (tmp[0] && tmp[1] && strcmp(tmp[0], "history") == 0)
		print_history(data, atoi(tmp[1]));
	else if (tmp[0] && strcmp(tmp[0], "history") == 0)
		print_history(data, -1);
	else if (tmp[0] && tmp[1] && strcmp(tmp[0], "unset") == 0)
		ft_unset(data->env, tmp[1]);
	else if (tmp[0] && strcmp(tmp[0], "unset") == 0)
		return ;
	else if (tmp[0] && strcmp(tmp[0], "exit") != 0)
		path_exec(data, tmp[0], &tmp[0]);
}

void	squotes_built_in(t_data *data)
{
	char		**tmp;
	t_commands	*cmd;

	cmd = data->history;
	while (cmd->next != NULL)
		cmd = cmd->next;
	tmp = cmd->squote_tab;
	replace_hash(tmp);
	second_squotes_built_in(data, tmp);
}
