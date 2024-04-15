/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:36:35 by aschmitt          #+#    #+#             */
/*   Updated: 2024/04/15 15:13:23 by aschmitt         ###   ########.fr       */
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
    int   fd;
    if (av[1])
        fd = open(av[1],  O_RDONLY, 0644);
    if (fd)
    {
        close(fd);
        printf("erere");
    }
        
    return 0;
}
