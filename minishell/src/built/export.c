/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   second_built_in.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/19 15:58:07 by marvin			#+#	#+#			 */
/*   Updated: 2024/07/16 15:44:08 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_new_env_var(char **env, char *var, char *value)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	env[i] = malloc(sizeof(char) * (strlen(var) + strlen(value) + 2));
	strcpy(env[i], var);
	env[i] = ft_strjoin(var, "=");
	env[i] = ft_strjoin(env[i], value);
	env[i + 1] = NULL;
}

char	*get_var(char *str)
{
	int		i;
	char	*tmp;	

	i = 0;
	while (str[i] != '=')
		i++;
	tmp = malloc(i + 1);
	ft_strlcpy(tmp, str, i + 1);
	return (tmp);
}

char	*get_value(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i + 1] == '\0')
		return (NULL);
	i++;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i + j])
	{
		tmp[j] = str[i + j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **env, char *str)
{
	char	*var;
	char	*value;

	if (check_str(str) == 1)
		return ;
	var = get_var(str);
	value = get_value(str);
	if (check_existing_var(env, var) == 1)
		change_var_value(env, var, value);
	else
	{
		create_new_env_var(env, var, value);
		free(var);
		free(value);
	}
}
