/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   print_history.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: marvin <marvin@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/23 14:40:48 by marvin			#+#	#+#			 */
/*   Updated: 2024/07/16 15:49:20 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_history(t_data *data, int print_nb)
{
	t_commands	*tmp;
	int			i;

	i = 0;
	if (print_nb < 0)
		print_nb = 1000;
	tmp = data->history;
	while (tmp != NULL)
	{
		if (i >= print_nb)
			break ;
		printf("%i: %s\n", i, tmp->prompt_command);
		tmp = tmp->next;
		i++;
	}
}
