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

//загрузка значения из команды в регистр каретки
//Циклы до исполнения 5

void				ld(t_cor *cor, t_process *proc)
{
//	//переменные
	// число из первого арг, если 1 рег - T_DIR, или число из адреса, если 2 рег - T_IND
	//номер регистра каретки, который передается как 2 аргумент
	//вычисленный адрес, если 2 рег - T_IND
	uint8_t			reg2;
	int32_t			value_to_reg;

	value_to_reg = get_value(cor, proc, 0);
	if (value_to_reg == MEM_SIZE + 1)
		return;
	reg2 = byte_to_int32(cor, proc, 1, cor->buffer_sizes[1]);
	proc->reg[reg2 - 1] = value_to_reg;
	if (value_to_reg == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
	//движение дальше
	//шаг курсора - прибавляем стандартный

	//получение данных
	//аргументы из операции
	//число из поля по адресу

	//изменения в структуре каретки
	//1- если аргумент T_DIR, загружаем значение из 2 аргумента в регистр. Если значение == 0, carry  = 1, в ост
	//случаях carry = 0
	//2- если аргумент T_IND,
	// 1) адрес = текущая позиция + <ПЕРВЫЙ_АРГУМЕНТ> % IDX_MOD
	// 2) считываем 4 байта с адреса
	// 3) записываем считанное число в регистр (переданный как 2 арг)

//	//печать
//	// ft_printf("P %4d | ld %d r%d\n", cursor_id, value, r_id);
}
//
//inline static void	log_ld(uint32_t cursor_id, int32_t value, int32_t r_id)
//{
//	ft_printf("P %4d | ld %d r%d\n", cursor_id, value, r_id);
//}
//
//void				op_ld(t_vm *vm, t_cursor *cursor)
//{
//	int32_t	value;
//	int32_t	r_id;
//
//	cursor->step += (OP_CODE_LEN + ARGS_CODE_LEN);
//	value = get_op_arg(vm, cursor, 1, true);
//	cursor->carry = (t_bool)(!value);
//	r_id = get_byte(vm, cursor->pc, cursor->step);
//	cursor->reg[INDEX(r_id)] = value;
//	cursor->step += REG_LEN;
//	if (vm->log & OP_LOG)
//		log_ld(cursor->id, value, r_id);
//}
//
/////
//
//void	carriage_ld_hub(t_carriage *carriage, unsigned char *arena)
//{
//	int		arg1;
//	int		arg2;
//	t_types	*types;
//
//	carriage->jump =
//			calculate_jump(carriage->current_opcode, arena, carriage->current_position);
//	types = extract_types_2(arena[(carriage->current_position + 1) % 4096]);
//	if ((types->type1 == 2 || types->type1 == 3) && types->type2 == 1)
//	{
//		if (types->type1 == 2)
//			arg1 = extract_4_bytes(carriage->current_position + 2);
//		else
//			arg1 = carriage_ld_hub_assist(carriage);
//		if (types->type1 == 2)
//			arg2 = extract_1_byte(carriage->current_position + 6);
//		else
//			arg2 = extract_1_byte(carriage->current_position + 4);
//		if (arg2 >= 1 && arg2 <= 16)
//			carriage_ld(carriage, arg1, arg2);
//	}
//	free(types);
//	carriage_jump(carriage);
//}
//
//int		carriage_ld_hub_assist(t_carriage *carriage)
//{
//	int	temp;
//	int	arg1;
//
//	temp = extract_2_bytes(carriage->current_position + 2);
//	arg1 = (carriage->current_position +
//			(temp % IDX_MOD)) % 4096;
//	if (arg1 < 0)
//		arg1 = 4096 + arg1;
//	arg1 = extract_4_bytes(arg1);
//	return (arg1);
//}
//
///*
//** @desc If 'ld' command is executed by carriage,
//** @desc then it loads value argument into register argument.
//** @desc Changes carry if necessary.
//** @param t_carriage *carriage - carriage structure
//** @param int value - value to be loaded into register
//** @param int reg - register of carriage to receive value
//** @return void
//*/
//
//void	carriage_ld(t_carriage *carriage, int value, int reg)
//{
//	if (value == 0)
//		carriage->carry = 1;
//	else
//		carriage->carry = 0;
//	if (reg == 1)
//		carriage->r1 = value;
//	else if (reg == 2)
//		carriage->r2 = value;
//	else if (reg == 3)
//		carriage->r3 = value;
//	else if (reg == 4)
//		carriage->r4 = value;
//	else if (reg == 5)
//		carriage->r5 = value;
//	else if (reg == 6)
//		carriage->r6 = value;
//	else if (reg == 7)
//		carriage->r7 = value;
//	else if (reg == 8)
//		carriage->r8 = value;
//	else if (reg == 9)
//		carriage->r9 = value;
//	else
//		carriage_ld_assist(carriage, value, reg);
//}
//
//void	carriage_ld_assist(t_carriage *carriage, int value, int reg)
//{
//	if (reg == 10)
//		carriage->r10 = value;
//	else if (reg == 11)
//		carriage->r11 = value;
//	else if (reg == 12)
//		carriage->r12 = value;
//	else if (reg == 13)
//		carriage->r13 = value;
//	else if (reg == 14)
//		carriage->r14 = value;
//	else if (reg == 15)
//		carriage->r15 = value;
//	else if (reg == 16)
//		carriage->r16 = value;
//}