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

#include "corwar.h"
#include "g_corewar_op.h"

//записывает значение регистра, переданного в качестве первого параметра,
// по адресу —
// текущая позиция + (<ЗНАЧЕНИЕ_ВТОРОГО_АРГУМЕНТА> + <ЗНАЧЕНИЕ_ТРЕТьЕГО_АРГУМЕНТА>) % IDX_MOD.
// Размер T_DIR 2.
//Циклы до исполнения 25

void				sti(t_cor *cor, t_process *proc)
{
	uint8_t			reg1;
	int32_t			regvalue;
	uint32_t		value2;
	uint32_t		value3;
	uint32_t		address;

	reg1 = cor->map[proc->pos + 2];
	regvalue = proc->reg[reg1];
	value2 = byte_to_int32(cor, proc, 1, cor->buffer_sizes[1]);
	value3 = byte_to_int32(cor, proc, 2, cor->buffer_sizes[2]);
	address = proc->pos + (value2 + value3) % IDX_MOD;

	ft_printf("address:%d", address);
	ft_printf("---map1:%d", cor->map[address]);
	ft_printf("---map2:%d", cor->map[address] + 1);
	ft_printf("---map3:%d", cor->map[address] + 2);
	ft_printf("---map4:%d\n", cor->map[address] + 3);

	value32_to_map(cor, -1, address, DIR_SIZE);

	ft_printf("address:%d", address);
	ft_printf("---map1:%d", cor->map[address]);
	ft_printf("---map2:%d", cor->map[address] + 1);
	ft_printf("---map3:%d", cor->map[address] + 2);
	ft_printf("---map4:%d\n", cor->map[address] + 3);

	print_arena(cor->map, 64);
}

