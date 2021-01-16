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

void make_buffer_codes(t_cor *cor)
{
	int	i;

	i = 0;
	cor->buffer_codes = (int *)malloc(sizeof(int) * 4);
	while (i < 4)
	{
		cor->buffer_codes[i] = 0;
		i++;
	}
	cor->buffer_counter = 0;
	i = 0;
	cor->buffer_sizes = (int *)malloc(sizeof(int) * 4);
	while (i < 4)
	{
		cor->buffer_sizes[i] = 0;
		i++;
	}
}

void	fill_buffer_with_zeros(t_cor *cor)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cor->buffer_codes[i] = 0;
		i++;
	}
	i = 0;
	while (i < 4)
	{
		cor->buffer_sizes[i] = 0;
		i++;
	}
	cor->buffer_counter = 0;
}

int32_t		get_address(t_process *process, int32_t step)
{
	int32_t	address;

	address = process->pos + step;
	if (address > MEM_SIZE)
		address = address - MEM_SIZE;
	process->cycle_to_exec = -1;
	return (address);
}
