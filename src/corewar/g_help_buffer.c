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

void 				make_alt_buffers(t_cor *cor)
{
	uint32_t 			*buf_proc_id; ////alter
	int32_t 			*reg[REG_NUMBER + 1]; 	////Array of variables for storing data
	uint8_t 			*carry;					//A special variable that affects the operation of the "zjmp" function and can
// ** take one of two values: 1 or 0. If it's 1, then the function updates the ** "position
	uint32_t 			*pos; 					////Map address
	uint8_t 			*op_code; 				//Contains the operation code, at the time of moving to this position on the map
//uint8_t				name_op;
//uint32_t			next_pos;
	int					*cycle_to_exec; 			// A counter containing the number of cycles that the carriage must wait before starting an operation.
	int32_t				*live_last_cycle; 		// Contain the cycle on which the last live operation was performed //gala убрала u
	uint32_t			*live_last_id;
	uint32_t			*id; 					//// index of process
	uint32_t			*player_id;
	t_op				*op;						// (gala) функция операции
	int					alt_buf_counter;
}

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

int	check_flag(t_cor *cor)
{
	if (cor->flag.dump64 == (int) cor->cycle && cor->flag.dump64 != 0)
	{
		print_arena(cor->map, 64);
		exit(0);
	}

	if (cor->flag.dump32 == (int) cor->cycle && cor->flag.dump32 != 0)
	{
		print_arena(cor->map, 32);
		exit(0);
	}
	return (0);
}
