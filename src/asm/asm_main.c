/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 11:12:51 by dcapers           #+#    #+#             */
/*   Updated: 2020/12/20 12:37:09 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include "libft.h"

void	print_help(void)
{
	ft_putstr("Usage: ./asm (champion.s)\n");
	ft_putstr("    champion.s   — from assemble to bytecode\n");
}

int				main(int ac, char **av)
{
	if (ac == 2 && is_true_ext(av[1], ".s"))
		assemble(av[1]);
	else
		print_help();
}