/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   check_pipes_redirections_quotes.c				  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/15 10:31:46 by nherbal		   #+#	#+#			 */
/*   Updated: 2024/07/16 16:40:22 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_cringe(char *tmp, int dquotes, int squotes, int i)
{
	if (tmp[i + 1] && ((tmp[i] == '>' || tmp[i] == '<')
			|| (tmp[i] == '>' && tmp[i + 1] == '>')
			|| (tmp[i] == '<' && tmp[i + 1] == '<'))
		&& (dquotes == 1 || squotes == 1))
		return (1);
	return (0);
}

int	check_pipes_redirections_quotes(char *tmp)
{
	int	i;
	int	dquotes;
	int	squotes;
	int	cringe;

	cringe = 0;
	dquotes = 0;
	squotes = 0;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"')
			dquotes++;
		if (tmp[i] == '\'')
			squotes++;
		if (tmp[i] == '|' && (dquotes == 1 || squotes == 1))
			cringe++;
		cringe += create_cringe(&tmp[i], dquotes, squotes, i);
		if (cringe != 0)
			return (1);
		i++;
	}
	return (0);
}
