/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:58:03 by msoulaim          #+#    #+#             */
/*   Updated: 2021/04/03 17:19:26 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

/*
** coloring options
*/
# define RED "\033[1;31m"
# define BLUE "\033[34m"
# define DEFAULT "\033[0m"

typedef	struct	s_shell
{
	char		**env;
	int			last_ret;
}				t_shell;

void			env_dup(char **env, t_shell *shell);
char			*get_var_env(char *var, t_shell *shell);
char			*get_cwd(t_shell *shell);
void			free_until(char **str, int n);
int				free2dim(char ***pointer);
void			ft_put4str(char *a, char *b, char *c, char *d);
char			**d_realloc(char **str, int new_size);
char			*join_three(char *str1, char *str2, char *str3);
int				str2len(char **str);
char			*replace_in_str(char *haystack, char *needle, char *str);
int				posend_var(char *str);
char			*joinf(char **str1, char **str2);
char			*joinc(char **str, char c);
char			*var_cr(char *str, t_shell *shell);
int				ft_echo(char **args);
int				ft_cd(char **args, t_shell *shell);
int				ft_setenv(char **args_cmd, t_shell *shell);
int				ft_unsetenv(char **args, t_shell *shell);
void			set_env(char *arg1, char *arg2, t_shell *shell);
char			*handle_home(char *str, t_shell *shell);
void			print_env(t_shell *shell);
void			handle_dollar(char **input, t_shell *shell);
char			*skip_all_dollars(char *str);
char			*skip_all(char *str, char c1, char c2);
void			exe(char *in, t_shell *shell);
#endif
