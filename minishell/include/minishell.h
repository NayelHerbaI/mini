/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nherbal <nherbal@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/14 11:32:41 by naherbal		  #+#	#+#			 */
/*   Updated: 2024/07/19 12:35:05 by nherbal		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>

# define MAX_LINE 1024
# define MAX_ARGS 64

typedef struct s_commands
{
	char				*prompt_command; //
	char				**cmds_tab; //
	char				*dq_cmd;
	char				**dquotes_tab;
	char				*sq_cmd;
	char				**squote_tab;
	char				**pipe_tab; //
	char				**tokens; //
	struct s_commands	*next;
}				t_commands;

typedef struct s_data
{
	char				*input_file; //
	char				*output_file; //
	int					append;
	int					here_document;
	int					pipe_index;
	char				**dir_tab; //
	char				*args[MAX_ARGS];
	int					num_commands;
	int					*pipefd;
	int					pipe_indices[MAX_ARGS];
	int					exit;
	int					arg_count;
	int					first_node;
	int					last_return_value;
	char				**env;
	struct sigaction	sa;
	int					p;
	int					built;
	t_commands			*history;
}				t_data;

void	setup(t_data *data, char **env);
void	first_node_creation(t_data *data, char *tmp);
void	create_last_node(t_data *data, char *tmp);
void	free_data(t_data *data);
void	free_commands_list(t_commands *head);
void	path_exec(t_data *data, char *cmd, char **args);
char	*secure_path(char **env, char *cmd, t_data *data);
int		check_dquotes(char *cmd);
char	*remove_dquotes(char *cmd);
int		check_squotes(char *cmd);
char	*remove_squotes(char *cmd);
char	*rm_quotes(char *cmd, int start, int end);
void	handle_signal(int signal);
int		check_pipe(char *tmp);
void	pipe_handling(t_data *data);
void	parse_command(char *cmd, char **args, t_data *data);
int		check_redirection(char *tmp);
void	handle_here_document(const char *delimiter);
void	execute_redircommand(char **args, t_data *data);
char	*remove_dquotes(char *cmd);
char	*remove_squotes(char *cmd);
int		check_spec_echo(char *cmd, char **env);
int		check_dollar(char *tmp);
void	expr_fct(t_data *data, char *tmp);
int		check_pipes_redirections_quotes(char *tmp);
char	**create_tab(t_data *data);
char	*get_curr_cmd(t_data *data);
int		create_pipe_tab(char **tmp, int num_args, int *pipe_indices);
void	rm_tmp_quotes(char **tmp);
void	create_pipes(int num_commands, int *pipefd);
void	do_pipe(int pid, t_data *data, char **tmp, int i);
void	execute_command(char **args, t_data *data);
void	close_and_wait(t_data *data);
int		check_pipe(char *tmp);
void	second_parse_command(char *token, t_data *data, char **args);
void	second_execute_redircommand(t_data *data);
void	third_execute_redircommand(t_data *data, char **args);
void	for_pipes(char *tmp, t_data *data);
void	for_echo_dollar(char *tmp, t_data *data);
void	for_something(char *tmp, t_data *data);
void	for_redirections(char *tmp, t_data *data);
void	for_regular_commands(char *tmp, t_data *data);
void	for_dquotes(char *tmp, t_data *data);
void	for_squotes(char *tmp, t_data *data);
void	change_var_value(char **env, char *var, char *value);
int		check_existing_var(char **env, char *var);
void	built_in(t_data *data);
void	dquotes_built_in(t_data *data);
void	squotes_built_in(t_data *data);
int		ft_echo(char **env, char **args);
int		ft_cd(t_data *data, char *path);
void	ft_pwd(void);
int		ft_env(char **env);
void	ft_export(char **env, char *str);
int		ft_unset(char **env, char *name);
void	print_history(t_data *data, int print_nb);
int		echo_dollar(char **env, char *var);
int		only_dquotes(char *tmp);
int		only_squotes(char *tmp);
int		nb_args(char **args);
int		check_qmark(char *tmp);
void	for_null(t_commands *new);
void	for_fill_new(t_commands *new, char *tmp);
char	**ft_split(char *s, char c);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *str);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar(char c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		check_substr(char *str, char *substr);
char	*ft_substr(char *s, int start, size_t len);
void	*ft_memdel(void *ptr);
char	*ft_itoa(int nbr);
void	ft_putendl_fd(char *s, int fd);
void	for_unset(t_data *data, char **tmp);
void	for_print_nb_history(t_data *data, char **tmp);
void	for_print_history(t_data *data, char **tmp);
void	for_exit(t_data *data, char **tmp);
void	for_path_exec(t_data *data, char **tmp);
void	for_dollar_echo(t_data *data, char **tmp);
void	for_pwd(t_data *data, char **tmp);
void	for_export(t_data *data, char **tmp);
void	for_env(t_data *data, char **tmp);
void	for_cd(t_data *data, char **tmp);
void	for_expr(t_data *data, char *tmp);

#endif
