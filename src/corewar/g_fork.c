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

//делает копию каретки. И эту копию размещает по адресу <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD.
// Размер T_DIR 2.
//Циклы до исполнения 800

void 				dublicate_process(t_process *dubl, t_process *proc)
{
	int 			index;

	index = -1;
	while (++index < REG_NUMBER)
		dubl->reg[index] = proc->reg[index];
	dubl->carry = proc->carry;
	dubl->live_last_cycle = proc->live_last_cycle; //(gala) изменила 17.01
	dubl->live_last_id = proc->live_last_id;
	dubl->id = 10; ///del
}

void				g_fork(t_cor *cor, t_process *proc)
{
	int32_t			arg1;
	int32_t			address;
	t_process 		*dubl;

	arg1 = get_value(cor, proc, 0);
	address = proc->pos + arg1 % IDX_MOD;
	if (address > MEM_SIZE)
		address = address % MEM_SIZE;
	dubl = init_process(address, cor->process, proc->player_id);
	dublicate_process(dubl, proc);
	push_back_vec(&cor->process, dubl);
	cor->count_cursors++;
}