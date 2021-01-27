/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 03:19:18 by dcapers           #+#    #+#             */
/*   Updated: 2020/12/20 12:36:59 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "includes/op.h"
#include "asm_errors.h"
#include "libft.h"

void				token_error(t_token *token)
{
	ft_putstr_fd("Unexpected token \"", 2);
	ft_putstr_fd(token->content, 2);
	ft_putstr_fd("\" at [", 2);
	ft_putnbr_fd(token->row, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(token->col, 2);
	ft_putstr_fd("]\n", 2);
	exit(1);
}

void	label_error(t_token *token)
{
	ft_putstr_fd("Undeclared label \"", 2);
	ft_putstr_fd(token->content, 2);
	ft_putstr_fd("\" is mentioned at [", 2);
	ft_putnbr_fd(token->row, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(token->col, 2);
	ft_putstr_fd("]\n", 2);
	exit(1);
}

void	operator_error(t_token *token)
{
	ft_putstr_fd("Unknown operator \"", 2);
	ft_putstr_fd(token->content, 2);
	ft_putstr_fd("\" at [", 2);
	ft_putnbr_fd(token->row, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(token->col, 2);
	ft_putstr_fd("]\n", 2);
	exit(1);
}

void	info_error(int error_code)
{
	ft_putstr_fd("Champion ", 2);
	ft_putstr_fd(!error_code ? "name" : "comment", 2);
	ft_putstr_fd(" too long (Max length: ", 2);
	ft_putnbr_fd(!error_code ? PROG_NAME_LENGTH : COMMENT_LENGTH, 2);
	ft_putstr_fd(")\n", 2);
	exit(1);
}

void	type_error(t_token *t, t_op *op, int arg_num)
{
	ft_putstr_fd("Invalid type of paramete", 2);
	ft_putnbr_fd(arg_num, 2);
	ft_putstr_fd("for instruction \"", 2);
	ft_putstr_fd(op->name, 2);
	ft_putstr_fd("\" at [", 2);
	ft_putnbr_fd(t->row, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(t->col, 2);
	ft_putstr_fd("]\n", 2);
}
