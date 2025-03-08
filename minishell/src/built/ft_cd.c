/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naherbal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:45:43 by naherbal          #+#    #+#             */
/*   Updated: 2024/07/16 15:46:27 by naherbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(t_data *data, char *path)
{
	char	*tmp;
	char	cwd[1024];

	if (path == NULL)
	{
		fprintf(stderr, "Path is NULL\n");
		return (-1);
	}
	if (chdir(path) != 0)
	{
		perror("BAHAHHAAH YOU SUCK. Can't even type the right directory...");
		return (-1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd failed");
		return (-1);
	}
	tmp = ft_strjoin("PWD", cwd);
	ft_export(data->env, tmp);
	free(tmp);
	return (0);
}
