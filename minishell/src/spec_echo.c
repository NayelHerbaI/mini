/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   spec_echo.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/06 18:35:51 by nherbal		   #+#	#+#			 */
/*   Updated: 2024/07/16 17:40:33 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_dollar(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

int	check_second_arg(char *echo, char **env)
{
	int		i;
	char	*tmp;

	tmp = &echo[1];
	i = 0;
	tmp = ft_strjoin(tmp, "=");
	while (env[i])
	{
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_env_var(char *echo, char **env)
{
	int		i;
	char	*tmp;
	int		len;

	tmp = &echo[1];
	len = ft_strlen(tmp);
	tmp[len] = '\0';
	tmp = ft_strjoin(tmp, "=");
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0)
		{
			printf("\'%s\'\n", &env[i][len + 1]);
			break ;
		}
		i++;
	}
}

void	double_sdquotes(char **tmp, char **env, char *echo)
{
	if (tmp[1][0] == '\'')
		printf("\"%s\"\n", echo);
	if (tmp[1][0] == '\"')
		print_env_var(echo, env);
	return ;
}

int	check_spec_echo(char *cmd, char **env)
{
	char	**tmp;
	char	*echo;

	tmp = ft_split(cmd, ' ');
	if (tmp[1] && check_dquotes(tmp[1]) == 0)
		echo = remove_dquotes(tmp[1]);
	else if (tmp[1] && check_squotes(tmp[1]) == 0)
		echo = remove_squotes(tmp[1]);
	if (tmp[0] && tmp[1] && strcmp(tmp[0], "echo") == 0
		&& check_squotes(tmp[1]) == 0 && check_dquotes(tmp[1]) == 0)
	{
		echo = remove_squotes(echo);
		double_sdquotes(tmp, env, echo);
		return (2);
	}
	else if (tmp[0] && tmp[1] && strcmp(tmp[0], "echo") == 0
		&& check_second_arg(echo, env) == 1 && check_squotes(tmp[1]) == 0)
	{
		printf("%s\n", echo);
		return (1);
	}
	return (0);
}
