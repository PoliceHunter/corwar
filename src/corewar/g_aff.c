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

//Эта операция берет значение из регистра, который был передан в качестве
// единственного аргумента. Приводит его к типу char. И выводит на экран как ASCII-символ.
//Циклы до исполнения 2

void				aff(t_cor *cor, t_process *proc)
{
	uint8_t			regnum1;
	int32_t			value;

	regnum1 = get_value(cor, proc, 0);
	value = proc->reg[regnum1];
	//Приводим его к типу char aff_symbol = (char)value;									DIR_SIZE);
	//if (cor->display_aff)
	//	ft_printf("Aff: %c\n", (char)value);

//???????
}