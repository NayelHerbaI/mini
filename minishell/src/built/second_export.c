/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nherbal <nherbal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 12:32:56 by nherbal           #+#    #+#             */
/*   Updated: 2024/07/19 17:00:09 by nherbal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_existing_var(char **env, char *var)
{
	int		i;
	int		j;
	char	cmp[1024];

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
		{
			cmp[j] = env[i][j];
			j++;
		}
		cmp[j] = '\0';
		if (strcmp(var, cmp) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	second_change_var_value(char **env, char *cmp, int i)
{
	int	j;

	j = 0;
	while (env[i][j] != '=')
	{
		cmp[j] = env[i][j];
		j++;
	}
	cmp[j] = '\0';
}

void	change_var_value(char **env, char *var, char *value)
{
	int		i;
	char	cmp[1024];

	i = 0;
	while (env[i])
	{
		second_change_var_value(env, cmp, i);
		if (strcmp(var, cmp) == 0)
		{
			strcpy(env[i], var);
			env[i] = ft_strjoin(var, "=");
			if (value != NULL)
				env[i] = ft_strjoin(env[i], value);
			else
				env[i][ft_strlen(env[i])] = '\0';
		}
		i++;
	}
	return ;
}
