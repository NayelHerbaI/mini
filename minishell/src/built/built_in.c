/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naherbal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:32:46 by naherbal          #+#    #+#             */
/*   Updated: 2024/07/16 15:34:23 by naherbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	for_echo(t_data *data, char **tmp)
{
	if (tmp[0] && tmp[1] && strcmp(tmp[1], "$?") != 0
		&& strcmp(tmp[0], "echo") == 0 && data->built == -1)
	{
		ft_echo(data->env, tmp);
		data->built = 1;
	}
}

void	built_in(t_data *data)
{
	char		**tmp;
	t_commands	*cmd;

	data->built = -1;
	cmd = data->history;
	while (cmd->next != NULL)
		cmd = cmd->next;
	tmp = cmd->cmds_tab;
	for_echo(data, tmp);
	for_dollar_echo(data, tmp);
	for_pwd(data, tmp);
	for_export(data, tmp);
	for_env(data, tmp);
	for_cd(data, tmp);
	for_print_history(data, tmp);
	for_print_nb_history(data, tmp);
	for_unset(data, tmp);
	for_exit(data, tmp);
	for_path_exec(data, tmp);
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		return (perror("getcwd failed"));
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}
