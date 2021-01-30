/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljacquet <ljacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:56:21 by ljacquet          #+#    #+#             */
/*   Updated: 2020/12/18 14:48:30 by ljacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corwar.h"
#include "../../includes/g_corewar_op.h"

//делает копию каретки. И эту копию размещает по адресу текущая позиция  +
// <ПЕРВЫЙ_АРГУМЕНТ> БЕЗ % IDX_MOD.
// Размер T_DIR 2.
//Циклы до исполнения 1000

void				lfork(t_cor *cor, t_process *proc)
{
	int32_t		address;
	t_process 		*dubl;

	address = proc->pos + get_value(cor, proc, 0);
	if (address < 0)
	{
		cor->valid_fork = 0;
		return;
	}

	if (address > MEM_SIZE)
		address = address % MEM_SIZE;
	dubl = init_process(address, cor->process, proc->player_id);
	dublicate_process(dubl, proc);
	push_front_vec(&cor->process, dubl);
	cor->count_cursors++;
	cor->valid_fork = 1;
	//ft_printf("lfork\n");
}