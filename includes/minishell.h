/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:17:55 by aleferra          #+#    #+#             */
/*   Updated: 2022/05/31 14:17:06 by lfilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enums.h"
# include "structure.h"
# include "error.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <limits.h>

# define PROMPT_SYMBOL "\033[0;32m➜ \033[0m"
# define ERROR_PROMPT_SYMBOL "\033[0;31m➜ \033[0m"
# define CLOSE_PROMPT_SYMBOL "Minishell is closing Bye!\n"
# define HEREDOC_PROMPT_SYMBOL "heredoc> "

/** global **/
int			g_status;

/** ----------------------------------------------app---------------------- **/

/** expand **/
void		expand_fd(t_cmd *cmd);

/** init **/
t_app		ft_init_app(char **env);

/** lexer **/
t_chain		*lexer(char *str);

/** start_app **/
int			start_app(t_app *app);
void		close_minishell(t_app *app);

/** pipe **/
void		ft_pipe(t_cmd *tmp, t_app **app, int pipe_nb);
void		ft_have_pipe(t_app **app, t_cmd **command, char *line);

/** syntaxer **/
int			syntaxer(t_chain *tokens);

/** ---------------------------------- builtins ------------------------ **/
/** echo **/
void		ft_echo(t_app *app, t_cmd *cmd);

/** exit **/
void		our_exit(t_app *app, t_cmd *cmd, int pipe);
int			is_only_num(char *s);
long long	ft_atoi_exit(const char *str, int i);

/** dispatcher **/
void		dispatch(t_app **app, t_cmd *cmd, int pipe);
void		expand_fd(t_cmd *cmd);

/** env **/
void		our_env(t_cmd *cmd, t_app *app);

/** unset **/
void		unset(t_cmd *cmd, t_app **app, int pipe);

/** pwd **/
void		pwd(t_app *app);

/** export **/
void		export(t_cmd *cmd, t_app **app, int pipe);

/** cd **/
void		cd(t_cmd *cmd, t_app *app, int pipe);
int			last_backslash(char *s);
int			get_old_dir(t_app *app, int pipe);
int			change_dir(t_app *app, char *s, int pipe);
int			go_in_dir(t_app *app, char *s, int pipe);
void		create_oldpwd(t_app *app, int pipe);

/** -----------------------init--------------------------------------- **/
/** init_choin **/
t_chain		*ft_add_new_chain(char c, int index);
void		ft_add_back_chain(t_chain **start, t_chain *new);

/** init_env **/
t_env		*ft_add_new_env(char *str);
t_env		*ft_init_env(char **env);
void		ft_add_back_env(t_env **env, t_env *new);
int			ft_end_env(char *str, int start);
char		*ft_expand_env(t_app *app, char *str);

/** --------------------------------------parse---------------------- **/
/** catch_error **/
void		catch_error(int err, t_chain *tokens);

/** clean_quote **/
char		*remove_q_or_dq(char *str);
int			have_q_or_dq(char *str);
char		*clean_args(char *cmd, t_app *app);

/** parse **/
char		**parse_quotes(char *s);
t_cmd		*split_arg(char *str, t_app *app);
t_bool		is_all_env(t_cmd *cmd);

/** token **/
t_token		ft_token(char c);
t_token		arg_type(char *s, int *mode);
int			is_env(char *str);

/** arg **/
char		**get_args(t_app *app, char **split);
char		*clean_args(char *cmd, t_app *app);
t_bool		is_only_redir(char *s);
int			check_redir(char *s, size_t *i);
size_t		last_redir(char *s);
int			get_args_count(char **s);

/** quote **/
char		**split_quote(char *str);

/** name **/
char		*get_name(char **str, int i);
char		*find_cmd_name(t_app *app, char **str);
char		**get_full_name(char *name, char **args);

/**------------------------redirection --------------------------------**/
/** utils_cmd **/
int			count_cmds(char **args);
char		**get_cmds(char *str, int err);
char		*create_cmd(char **args, int *pos);
void		is_valid_fd(t_app *app, char *file);

/** out **/
int			find_redir_out(t_app *app, char **s);
int			create_redir_out(t_app *app, char **s, size_t i);

/** in **/
int			find_redir_in(t_app *app, char **s, char *name);
char		**split_redir_in(char *s, char *next);

/** heredoc **/
int			handle_heredoc(int input_fd, t_app *app, char *del);
int			is_heredoc(char *s);
int			read_heredoc(t_app *app, char **s, size_t i);

/** ----------------------------utils----------------------------------- **/
/** tab_env **/
char		**ft_tab_env(t_env *env);
void		add_name_env(t_app *app, char *str, t_env **env, int pipe);
void		change_the_env(char *str, char *tempo, t_env *tmp);

/** paths **/
int			rigth_path(t_app *app, char *s, int pipe);
int			path_with_cdpath(t_app *app, char *s);
int			path_exists(char *s);

/** native_paths **/
char		**get_all_paths(t_app **app);
int			native_path_exists(char **paths, char *cmd);
char		*get_native_path(t_app **app, char *cmd);

/** redirection **/
int			is_redir(char *s);
t_bool		is_real_out_redir(char *s, int *mode);
t_bool		is_real_in_redir(char *s, int *mode);
t_bool		is_real_heredoc_redir(char *s, int *mode);

/** errors **/
void		print_err_cd(t_app *app, char *cmd, int err, int pipe);
void		print_err_exit(t_app *app, char *cmd, int err, int pipe);
void		print_err_token(t_app *app);
void		print_fd_err(t_app *app, char *cmd);
void		print_ambiguous_err(t_app *app, char *name);

/** reset_str **/
void		reset_str(char **str, char *new);
char		*res_str(char **str, char *new);
t_token		is_a_pipe(size_t len, size_t i);
size_t		array_length(char **str);
int			is_builtin(char *s);

/** permissions **/
int			check_cmd(t_app *app, t_cmd *cmd);

/** export **/
void		ft_add_export(t_app *app, t_env **env, char *str, int pipe);
void		print_export_err(t_app *app, char *str);
t_bool		is_a_plus(char *tempo, t_env *tmp);
void		ft_concat(char *str, t_env *tmp);

/** last cmd **/
int			ft_last_cmd(t_app *app, t_cmd **com);
int			check_builtins(t_cmd *cmd, t_app *app);
int			ft_check_cd(t_cmd *cmd, t_app *app);
int			ft_check_unset(t_cmd *cmd, t_app *app);
int			ft_check_exit(t_app *app, t_cmd *cmd);
int			ft_check_pwd(t_app *app);

/** heredoc **/
char		*find_env(char *str, t_app *app);
void		handle(char *line, int p_fd[2], int test, t_app *app);
void		catch_new_signal(int signal);

/** in_utils **/
int			which_input(t_app *app, char *file, char *name);
int			file_next_in(t_app *app, char *s, char *next);
int			next_r_in(char *s);
int			count_nb_redirs_in(char *s);

/** out_utils **/
int			find_last_outredir(char *s);
int			file_next_out(t_app *app, char *s, char *next);
int			which_output(t_app *app, char *s, char *file);
int			next_r_out(char *s);
int			count_nb_redirs(char *s);

/** nu **/
char		**get_args_nu(char **s);
char		*find_cmd_name_nu(t_app *app, char **str);

/**arg**/
char		**get_args_clean(t_app *app, char **s, int index, size_t i);

/** --------------other----------------- **/
/** catch_signal **/
void		init_termios(t_app *app, int nb);
void		catch_signal(t_app *app);
void		catch_pipe_signal(void);
void		pipe_signal_handler(int signo);
void		default_signal_handler(int signo);

/**free_app**/
void		free_app(t_app *app);

/** free **/
void		free_array(char **array);
void		free_cmd(t_cmd *cmd);
void		free_env(t_env *env);
void		free_end(char *line, t_cmd *command);
void		free_both(char *line, char *arg);

/** token **/
int			check_for_three(t_chain *tmp);
int			check_for_two(t_chain *tmp);
t_bool		check_unsupported_tokens(t_cmd *cmd);

/** env **/
char		*get_env(t_app *app, char *str);
char		*get_env_cd(t_app *app, char *str);
void		set_env(t_app *app, char *env1, char *new);

t_cmd		*init_cmd(t_app *app, char **str);
int			has_permission(t_app *app, char *test);
#endif