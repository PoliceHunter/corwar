/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 02:38:08 by dcapers           #+#    #+#             */
/*   Updated: 2020/12/20 12:36:51 by dcapers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_op.h"
#include "asm_errors.h"
#include "unistd.h"

t_token			*create_token(t_parser *p, t_type type)
{
	t_token			*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		kill_exe(ERR_TOKEN_INIT);
	token->content = NULL;
	token->row = p->row;
	token->type = type;
	token->col = p->col;
	token->next = NULL;
	return (token);
}

void			add_token(t_parser *p, t_token *token)
{
	t_token		*tmp;

	if (!p || !token)
		return;
	if (!p->token)
		p->token = token;
	if (p->last)
		p->last->next = token;
	p->last = token;	
}
