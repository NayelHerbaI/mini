/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: naherbal <naherbal@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/14 11:30:39 by naherbal		  #+#	#+#			 */
/*   Updated: 2024/07/20 18:09:44 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

static int	exit_fct(t_data *data)
{
	int			i;
	t_commands	*curr;

	curr = data->history;
	while (curr->next != NULL)
		curr = curr->next;
	i = 0;
	while (curr->cmds_tab[i])
	{
		if (strcmp(curr->cmds_tab[i], "exit") == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	get_line(t_data *data)
{
	char	*tmp;

	data->p = -1;
	tmp = readline("$> ");
	if (!(tmp))
		return ;
	if (!data->first_node)
		first_node_creation(data, tmp);
	else
		create_last_node(data, tmp);
	if (tmp && *tmp)
		add_history(tmp);
	if (exit_fct(data) == 1)
		data->exit = 1;
	for_expr(data, tmp);
	for_pipes(tmp, data);
	for_echo_dollar(tmp, data);
	for_something(tmp, data);
	for_redirections(tmp, data);
	for_regular_commands(tmp, data);
	for_dquotes(tmp, data);
	for_squotes(tmp, data);
	tmp = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	setup(data, env);
	while (data->exit == 0)
		get_line(data);
	free_data(data);
	return (0);
}
