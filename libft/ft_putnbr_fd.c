/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:20:07 by aschmitt          #+#    #+#             */
/*   Updated: 2023/11/14 17:38:59 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive_putnbr(int nb, int fd)
{
	if (nb / 10 == 0)
		ft_putchar_fd('0' + nb % 10, fd);
	else
	{
		ft_recursive_putnbr(nb / 10, fd);
		ft_putchar_fd('0' + nb % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	ft_recursive_putnbr(n, fd);
}
