/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:47:06 by marvin            #+#    #+#             */
/*   Updated: 2024/07/16 15:48:23 by naherbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	second_ft_echo(char **args, int n_option)
{
	int	i;

	i = 1;
	if (nb_args(args) > 1)
	{
		while (args[i] && strcmp(args[i], "-n") == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	return (n_option);
}

int	ft_echo(char **env, char **args)
{
	int	n_option;

	n_option = 0;
	if (nb_args(args) == 1 || (args[1]
			&& (strcmp(args[1], "\"\"") == 0 || strcmp(args[1], "\'\'") == 0)))
		return (write(1, "\n", 1));
	if (args[1][0] == '$' && strcmp(args[1], "$?") != 0)
	{
		echo_dollar(env, &args[1][1]);
		return (0);
	}
	n_option = second_ft_echo(args, n_option);
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
