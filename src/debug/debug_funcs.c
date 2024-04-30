/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:12:57 by jules             #+#    #+#             */
/*   Updated: 2024/04/30 10:37:42 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_type(int t)
{
	if (t == CMD)
		printf("CMD");
	else if (t == ARG)
		printf("ARG");
	else if (t == PIPE)
		printf("PIPE");
	else if (t == INFILE)
		printf("INFILE");
	else if (t == OUTFILE)
		printf("OUTFILE");
	else if (t == OUTFILE_APPEND)
		printf("OUTFILE_APPEND");
	else if (t == INFILE_HEREDOC)
		printf("INFILE_HEREDOC");
	else
		printf("NON RECONNU %d\n", t);
}

void	print_token(t_token t)
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
