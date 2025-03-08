/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   echo_dollar.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/28 03:53:31 by nherbal		   #+#	#+#			 */
/*   Updated: 2024/07/16 17:26:56 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo_dollar(char **env, char *var)
{
	int		i;
	char	*tmp;
	int		len;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			break ;
		i++;
	}
	len = ft_strlen(env[i]) - ft_strlen(var);
	tmp = ft_substr(env[i], ft_strlen(var) + 1, len);
	if (ft_putstr_fd(tmp, 1) == 0)
	{
		ft_putstr_fd("\n", 1);
		return (1);
	}
	else
		ft_putstr_fd("\n", 1);
	return (0);
}
