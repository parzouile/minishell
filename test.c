/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:36:35 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/12 12:54:06 by aschmitt         ###   ########.fr       */
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

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *s = "/bin/ls";
    char *args[4];
    args[0] = s;
    args[1] = "-l";
    args[2] = NULL;
    
    execve(s, args, envp);
}
