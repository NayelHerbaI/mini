/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naherbal <naherbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:47:56 by naherbal          #+#    #+#             */
/*   Updated: 2024/07/31 19:31:32 by naherbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_sigint_input(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigint_exec(int signum)
{
	// (void)signum;
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

void	config_signals_input(void)
{
	signal(SIGINT, handle_sigint_input);
	signal(SIGQUIT, SIG_IGN);
}

void	config_signals_exec(void)
{
	signal(SIGINT, handle_sigint_exec);
	signal(SIGQUIT, handle_sigint_exec);
}

void	setup(t_data *data, char **env)
{
	int	i;

	i = 0;
	data->exit = 0;
	data->first_node = 0;
	data->last_return_value = 0;
	data->env = env;
	config_signals_exec();
	config_signals_input();
	data->dir_tab = malloc(sizeof(char *) * 50);
	while (i < 50)
	{
		data->dir_tab[i] = malloc(sizeof(char) * 100);
		i++;
	}
}
