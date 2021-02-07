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

//влияет значение флага carry.  устанавливает куда должна переместиться
// каретка для выполнения следующей операции
// Размер T_DIR 2.
//Циклы до исполнения 20
//изменения в структуре каретки
//Если carry = 1, функция обновляет значение PC на адрес: текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD
//Если значение carry равно нулю, перемещение не выполняется.

void				zjmp(t_cor *cor, t_process *proc)
{
	int32_t			arg1;
	int32_t			jump;

	arg1 = byte_to_int32(cor, proc, 0, cor->buffer_sizes[0]);
	jump = arg1 % IDX_MOD;
	//proc->carry = 1;
	if (proc->carry == 1)
	{
		//proc->pos = get_address(proc, jump, 1); //перепрыгиваем операцию
		proc->op_step = jump;
		//proc->cycle_to_exec = -1;
	}
	/*else
	{
		proc->pos = get_address(proc, proc->next_step, 1);
	}*//////
}