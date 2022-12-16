/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoulaim <msoulaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:04:29 by msoulaim          #+#    #+#             */
/*   Updated: 2021/04/09 12:44:13 by msoulaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*input(t_shell *shell)
{
	int		ret;
	char	*c;
	char	buf[2];
	char	*tmp;

	buf[1] = '\0';
	c = ft_strdup("");
	while ((ret = read(0, buf, 1)) && buf[0] != '\n')
	{
		tmp = c;
		c = ft_strjoin(c, buf);
		free(tmp);
		if (c == NULL)
		{
			ft_putendl_fd("malloc failed at input()", 2);
			free_until(shell->env, INT_MAX);
			free(shell->env);
			exit(EXIT_FAILURE);
		}
	}
	return (c);
}

void		prompt(t_shell *shell)
{
	char	*user;
	char	*cwd = NULL;

	user = get_var_env("USER", shell);
	cwd = get_cwd(shell);
	if (user == NULL || ft_strlen(user) == 0)
		user = ft_strdup("no USER");
	ft_putstr("╭─");
	ft_put4str(RED, user, "@minishell ", BLUE);
	ft_put4str(cwd, DEFAULT, "\n", "╰─# ");
	ft_strdel(&user);
	ft_strdel(&cwd);
}

void		input_handler(char **input, t_shell *shell)
{
	char	*tmp;

	if (ft_strchr(*input, '$'))
		handle_dollar(input, shell);
	if (ft_strchr(*input, '~') && !ft_strchr(*input, '\"'))
	{
		tmp = *input;
		*input = handle_home(*input, shell);
		free(tmp);
	}
	if (ft_strchr(*input, '$'))
	{
		tmp = *input;
		*input = skip_all_dollars(*input);
		free(tmp);
	}
	if (ft_strchr(*input, '\'') || ft_strchr(*input, '"'))
		skip_all(*input, '\'', '"');
	if (ft_strchr(*input, '\t'))
		skip_all(*input, '\t', '\t');
}

void		exe_all_pv(char *in, t_shell *shell)
{
	char	**cmds;
	int		i;

	cmds = ft_strsplit(in, ';');
	i = 0;
	while (cmds && cmds[i])
	{
		exe(cmds[i], shell);
		i++;
	}
	if (cmds)
	{
		free_until(cmds, INT_MAX);
		free(cmds);
	}
}

int			main(int ac, char **av, char **env)
{
	char	*in;
	t_shell	shell;

	(void)av;
	(void)ac;
	env_dup(env, &shell);
	while (1)
	{
		prompt(&shell);
		in = input(&shell);
		if (!ft_strcmp(in, "exit") || !ft_strncmp(in, "exit ", 5))
		{
			free_until(shell.env, INT_MAX);
			free(shell.env);
			ft_strdel(&in);
			return (0);
		}
		input_handler(&in, &shell);
		exe_all_pv(in, &shell);
		ft_strdel(&in);
	}
	return (1);
}
