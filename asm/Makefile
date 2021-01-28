# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 12:04:51 by dcapers           #+#    #+#              #
#    Updated: 2020/12/21 18:44:35 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM_NAME = asm
CORE_NAME = corewar

SRC_DIR = src/
OBJ_DIR = obj/

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

ASM_INCLUDES = -I$(INCLUDES) \
				-I$(INC_LIBFT)

CORE_INCLUDES = -I$(INCLUDES) \
				-I$(INC_LIBFT)

ASM_DIR = asm/
CORE_DIR = corewar/

CORE_LIST = main.c \
            			exit.c \
            			g_op/g_add.c \
            			g_op/g_aff.c \
            			g_op/g_and.c \
            			g_op/g_fork.c \
            			g_op/g_game_in_cycle.c \
            			g_op/g_game_logic.c \
            			g_op/g_help_buffer.c \
            			g_op/g_ld.c \
            			g_op/g_ldi.c \
            			g_op/g_lfork.c \
            			g_op/g_live.c \
            			g_op/g_lld.c \
            			g_op/g_lldi.c \
            			g_op/g_or.c \
            			g_op/g_st.c \
            			g_op/g_sti.c \
            			g_op/g_sub.c \
            			g_op/g_xor.c \
            			g_op/g_zjmp.c \

CORE_SRC_DIR = $(SRC_DIR)$(CORE_DIR)


CORE_OBJ_DIR = $(OBJ_DIR)$(CORE_DIR)


CORE_OBJ_LIST = $(patsubst %.c, %.o, $(CORE_LIST))

CORE_OBJ = $(addprefix $(CORE_OBJ_DIR),  $(CORE_OBJ_LIST))


CORE_SRC = $(addprefix $(CORE_SRC_DIR), $(CORE_LIST))

LIBFT_ALL		= $(addsuffix .all,$(LIBFT_DIR))
LIBFT_CLEAN	= $(addsuffix .clean,$(LIBFT_DIR))
LIBFT_FCLEAN	= $(addsuffix .fclean,$(LIBFT_DIR))

INCLUDES		= includes/
INC_LIBFT	= $(addsuffix inc/,$(LIBFT_DIR))

CORE_HEADERS_LIST = op.h corwar.h g_op/g_corewar_op.h

FLAGS = 

all: $(LIBFT_ALL) $(CORE_NAME)

clean: $(LIBFT_CLEAN)
	@rm -rf $(ASM_OBJ_DIR) $(CORE_OBJ_DIR) $(OBJ_DIR)

fclean: $(LIBFT_FCLEAN) clean
	@rm -rf $(ASM_NAME) $(CORE_NAME)

re:		fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(CORE_OBJ_DIR):
	@mkdir -p $(CORE_OBJ_DIR)

$(CORE_NAME): $(LIBFT) $(OBJ_DIR) $(CORE_OBJ_DIR) $(CORE_OBJ)
	@gcc $(FLAGS) $(CORE_INCLUDES) $(CORE_OBJ) $(LIBFT) -o $(CORE_NAME)
	@echo "\033[32m$(CORE_NAME) binary created\033[0m."

$(ASM_OBJ_DIR)%.o : $(ASM_SRC_DIR)%.c $(ASM_HEADERS)
	@echo "\033[34mASM COMPILING:\033[0m" $< 
	@gcc $(FLAGS) -o $@ -c $< $(ASM_INCLUDES)

$(CORE_OBJ_DIR)%.o : $(CORE_SRC_DIR)%.c $(CORE_HEADERS)
	@echo "\033[34mASM COMPILING:\033[0m" $< 
	@gcc $(FLAGS) -c $(CORE_INCLUDES) $< -o $@

%.all:
	@make -C $*

%.clean:
	@make -C $* clean

%.fclean:
	@make -C $* fclean

.PHONY: all clean fclean re