/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:13:51 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/24 23:32:20 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(void)
{
	rl_clear_history();
	printf("\033[31;1mBye\033[0m\n");
	exit(0);
}

void	ft_error(char *s)
{
	perror(s);
	exit(1);
}

void	ft_ctrls(int sig)
{
	(void)sig;
}

void	display_prompt(char **envp)
{
	char	*s;

	(void)envp;
	s = NULL;
	using_history();
	signal(SIGINT, ft_ctrlc);
	signal(SIGQUIT, ft_ctrls);
	while (1)
	{
		s = readline("\033[32;1m$ User ->\033[0m ");
		if (!s)
			ft_exit();
		add_history(s);
		parsing(&s, envp);
		free(s);
	}
}
/*
int	main(int ac, char **av, char **envp)
{
	t_minishell	mini;
	int			exit_status;

	(void)av;
	if (ac != 1)
	{
		(void) write(2, "Error args\n", 11);
		return (EXIT_FAILURE);
	}
	mini = create_minishell(envp);
	if (!mini)
	{
		(void) write(2, "Error during setup\n", 19);
		return (EXIT_FAILURE);
	}
	exit_status = run_minishell(mini);
	free_minishell(mini);
	return (exit_status);
}
*/
void	print_type(int t)
{
	switch (t)
	{
		case ARG:
			printf("ARG");
			break ;
		case PIPE:
			printf("PIPE");
			break ;
		case INFILE:
			printf("INFILE");
			break ;
		case OUTFILE:
			printf("OUTFILE");
			break ;
		case OUTFILE_APPEND:
			printf("OUTFILE_APPEND");
			break ;
		case INFILE_HEREDOC:
			printf("INFILE_HEREDOC");
			break ;
		default:
			printf("NON RECONNU");
	}
}

void print_token(t_token t)
{
	if (!t)
		return ;
	printf("TYPE : ");
	print_type(t->type);
	printf("\n");
	if (t->str)
		printf("STR : %s\\n\n\n", t->str);
	print_token(t->next);
}

void	print_tenv(t_env env)
{
	if (!env)
		return ;
	printf("%s=%s\n", env->name, env->value);
	print_tenv(env->next);
}

void	print_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	mini;
	int			exit_status;

	(void)av;
	if (ac != 1)
	{
		(void) write(2, "Error args\n", 11);
		return (EXIT_FAILURE);
	}
	mini = create_minishell(envp);
	if (!mini)
	{
		(void) write(2, "Error during setup\n", 19);
		return (EXIT_FAILURE);
	}
	//char *line = get_next_line(0);
	// if (tokenize(&(mini->cmd_line), line))
	// 	printf("ERROR\n");
	// free(line);
	// print_token(mini->cmd_line);
	print_tenv(mini->env);
	printf("\n");
	char **env = tenv_to_arr(mini->env);
	print_envp(env);
	free_tab(env);
	exit_status = run_minishell(mini);
	free_minishell(mini);
	return (exit_status);
}