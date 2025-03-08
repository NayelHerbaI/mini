/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   quotes_handling.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/27 16:46:29 by naherbal		  #+#	#+#			 */
/*   Updated: 2024/07/16 17:30:49 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_dquotes(char *cmd) // ----> check si on a un nombre pair de quotes
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '"')
			count++;
		i++;
	}
	if (count == 0)
		return (1);
	if (count % 2 == 0)
		return (0);
	return (1);
}

char	*remove_dquotes(char *cmd)
{
	int	start;
	int	end;

	start = 0;
	while (cmd[start])
	{
		if (cmd[start] == '"')
			break ;
		start++;
	}
	end = start + 1;
	while (cmd[end])
	{
		if (cmd[end] == '"')
			break ;
		end++;
	}
	if (start == end - 1)
		return (NULL);
	return (rm_quotes(cmd, start, end));
}

int	check_squotes(char *cmd) // ----> check si on a un nombre pair de quotes
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			count++;
		i++;
	}
	if (count == 0)
		return (1);
	if (count % 2 == 0)
		return (0);
	return (1);
}

char	*remove_squotes(char *cmd)
{
	int	start;
	int	end;

	start = 0;
	while (cmd[start])
	{
		if (cmd[start] == '\'')
			break ;
		start++;
	}
	end = start + 1;
	while (cmd[end])
	{
		if (cmd[end] == '\'')
			break ;
		end++;
	}
	if (start == end - 1)
		return (NULL);
	return (rm_quotes(cmd, start, end));
}

char	*rm_quotes(char *cmd, int start, int end) // ABA
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	i = 0;
	tmp = malloc(ft_strlen(cmd) - 1);
	while (cmd[i])
	{
		if (i > start && cmd[i] == ' ')
		{
			tmp[j] = '#';
			j++;
			i++;
		}
		if (i == start || i == end)
			i++;
		tmp[j] = cmd[i];
		j++;
		if (!cmd[i])
			break ;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
