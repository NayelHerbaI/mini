/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   secure_path.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/25 20:30:23 by marvin			#+#	#+#			 */
/*   Updated: 2024/07/20 18:10:26 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

t_commands	*get_curr(t_data *data)
{
	t_commands	*curr;

	curr = data->history;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

char	**create_path(char *cmd, int i, char **env, t_data *data)
{
	int			j;
	char		*first_token;
	t_commands	*curr;

	curr = get_curr(data);
	j = 0;
	curr->tokens = ft_split(env[i], ':');
	first_token = ft_substr(curr->tokens[0], 5, 1000000);
	free(curr->tokens[0]);
	curr->tokens[0] = first_token;
	while (curr->tokens[j])
	{
		first_token = ft_strjoin(curr->tokens[j], "/");
		free(curr->tokens[j]);
		curr->tokens[j] = first_token;
		first_token = ft_strjoin(curr->tokens[j], cmd);
		free(curr->tokens[j]);
		curr->tokens[j] = first_token;
		j++;
	}
	return (curr->tokens);
}

char	*return_path(t_data *data, char *cmd)
{
	int			j;
	t_commands	*curr;

	curr = get_curr(data);
	j = 0;
	while (curr->tokens[j])
	{
		if (access(curr->tokens[j], X_OK) == 0)
			return (curr->tokens[j]);
		j++;
	}
	return (cmd);
}

char	*secure_path(char **env, char *cmd, t_data *data)
{
	int			i;
	t_commands	*curr;

	curr = get_curr(data);
	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (env[i])
	{
		if (check_substr(env[i], "PATH=") == 0)
			break ;
		i++;
	}
	if (env[i] == NULL || strcmp(env[i], "PATH=") == 0)
		return ("PATH=");
	if (!curr->tokens)
	{
		create_path(cmd, i, env, data);
		return (return_path(data, cmd));
	}
	else
		return (return_path(data, cmd));
}
