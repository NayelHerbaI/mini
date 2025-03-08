/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   unset.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/19 17:31:15 by marvin			#+#	#+#			 */
/*   Updated: 2024/07/16 15:54:27 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	env_len(char **env)
{
	int	len;

	len = 0;
	while (env[len] != NULL)
		len++;
	return (len);
}

int	ft_unset(char **env, char *name)
{
	int	name_len;
	int	env_length;
	int	i;
	int	j;

	i = 0;
	name_len = ft_strlen(name);
	env_length = env_len(env);
	while (i < env_length)
	{
		if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			j = i;
			while (j < env_length - 1)
			{
				env[j] = env[j + 1];
				j++;
			}
			env[env_length - 1] = NULL;
			return (0);
		}
		i++;
	}
	return (-1);
}
