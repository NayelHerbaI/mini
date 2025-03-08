/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   expr.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/15 07:51:07 by nherbal		   #+#	#+#			 */
/*   Updated: 2024/07/16 17:42:37 by naherbal         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

void	for_expr(t_data *data, char *tmp)
{
	if (strcmp(tmp, "expr $? + $?") == 0 || strcmp(tmp, "expr $?") == 0)
	{
		expr_fct(data, tmp);
		data->p = 1;
	}
}

int	check_qmark(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '?')
			return (0);
		i++;
	}
	return (1);
}

void	third_expr_fct(t_data *data, char *tmp)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i + 1] && ft_strncmp(&tmp[i], "$?", 2) == 0)
			total += data->last_return_value;
		i++;
	}
	printf("%d\n", total);
}

void	second_expr_fct(t_data *data, char *tmp)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (tmp[i])
	{
		if (tmp[i + 1] && ft_strncmp(&tmp[i], "$?", 2) == 0)
			total++;
		i++;
	}
	while (total > 0)
	{
		printf("%d", data->last_return_value);
		total--;
		if (total > 0)
			printf(" + ");
	}
	printf("\n");
}

void	expr_fct(t_data *data, char *tmp)
{
	if (check_squotes(tmp) == 0)
		printf("%s\n", &tmp[5]);
	else if (check_dquotes(tmp) == 0)
		second_expr_fct(data, tmp);
	else
	{
		third_expr_fct(data, tmp);
	}
	data->last_return_value = 0;
}
