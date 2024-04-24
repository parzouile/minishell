/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:36:35 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/24 11:30:42 by aschmitt         ###   ########.fr       */
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


typedef struct s_command
{
	char	*cmd;
	char	**args;
	int		infile;
	int		outfile;
}					t_command;


int	main(int argc, char **argv)
{
	t_command command;

	command.cmd = argv[0];
	command.infile = -2;
	command.outfile = -2;
	command.args = malloc(sizeof(char *) * 5);
	
	command.args[0] = "jean";
	command.args[1] = NULL;
	free(command.args);

	chdir("src/");
	
	return 0;
	
}