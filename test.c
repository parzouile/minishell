/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:36:35 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/16 13:02:17 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>


typedef struct s_token	*t_token;

struct s_token
{
	char	*str;
	int		type;
	t_token	prev;
	t_token	next;
};

int	nb_args(t_token line)
{
	int	i;

	i = 0;
	while ((line->type == 2  || line->type == 1))
	{
		i++;
		if (line->next == NULL)
			break;
		line = line->next;

	}
	printf("nb = %d\n", i);
	fflush;
	return (i);
}

char	**take_args(t_token *line)
{
	char	**result;
	int		i;
	int		j;

	i = nb_args(*line);
	result = (char **)malloc((i + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		result[j] = (*line)->str;
		(*line) = (*line)->next;
	}
	result[i] = NULL;
	return (result);
}


t_token new_token(char *s)
{
	t_token t;
	
	t = malloc(sizeof(t_token) * 1);
	t->str = s;
	return (t);
}
	
void	test(t_token  *token)
{
	printf("token = %s\n", (*token)->str);
	*token = (*token)->next;
	printf("token = %s\n", (*token)->str);
}

int main() 
{
		t_token token1;//= {"Element1", 2, NULL, NULL};
		t_token token2;// = {"Element2", 2, NULL, NULL};
		t_token token3;// = {"Element3", 2, NULL, NULL};
		token1 = malloc(sizeof(struct s_token));
		token2 = malloc(sizeof(struct s_token));
		token3 = malloc(sizeof(struct s_token));
		token1->str = "ls";
		token2->str = "-l";
		token3->str = "-a";
		
		token1->type = 1;
		token2->type = 2;
		token3->type = 2;
		
		token1->prev = NULL;
		token1->next = token2;
		token2->prev = token1;
		token2->next = token3;
		token3->prev = token2;
		token3->next = NULL;
		char **args = take_args(&token1);
		
		for (size_t i = 0; args[i]; i++)
		{
			printf("%s\n", args[i]);
		}

		

		return 0;
}



// typedef struct s_token	*t_token;
// typedef struct s_env	*t_env;

// struct s_token
// {
// 	char	*str;
// 	int		type;
// 	t_token	prev;
// 	t_token	next;
// };

// struct s_env
// {
// 	char	*value;
// 	t_env	next;
// };

// int	setup_env(t_env *env, char **envp)
// {
// 	if (!envp)
// 		return (1);
// 	if (!envp[0])
// 		return (0);
// 	*env = malloc(sizeof(struct s_env));
// 	if (!(*env))
// 		return (1);
// 	(*env)->next = NULL;
// 	(*env)->value = strdup(envp[0]);
// 	if (!(*env)->value && envp[0])
// 		return (1);
// 	return (setup_env(&((*env)->next), envp + 1));
// }


// size_t	env_len(t_env env)
// {
// 	if (!env)
// 		return (0);
// 	return (1 + env_len(env->next));
// }

// char	**tenv_to_arr(t_env	env)
// {
// 	char	**envp;
// 	size_t	i;
// 	size_t	len;

// 	len = env_len(env) + 1;
// 	envp = malloc(sizeof(char *) * len);
// 	if (!envp)
// 		return (NULL);
// 	i = 0;
// 	while (i + 1 < len)
// 	{
// 		envp[i] = env->value;
// 		env = env->next;
// 		i++;
// 	}
// 	envp[i] = NULL;
// 	return (envp);
// }

// void	test(t_env env)
// {
// 	printf("env = %s\n", env->value);
// 	env = env->next;
// 	printf("env = %s\n", env->value);
// 	env = env->next;
// 	printf("env = %s\n", env->value);
// }

// void	free_env(t_env env)
// {
// 	t_env	next;

// 	if (!env)
// 		return ;
// 	next = env->next;
// 	free(env->value);
// 	free(env);
// 	free_env(next);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env 	env;
	
// 	setup_env(&env, envp);
// 	printf("envaa = %s\n", env->value);
// 	char **a = tenv_to_arr(env);
// 	printf("s = %s\n", a[0]);
// 	for (size_t i = 0; a[i]; i++)
// 	{
// 		printf("s = %s\n", a[i]);
// 	}
// 	free(a);
// 	free_env(env);
	
// }

// int	main()
// {
// 	int fd = open("test", O_WRONLY , 644);
// 	dup2(3, STDOUT_FILENO);
// 	printf("ezeez");
// }