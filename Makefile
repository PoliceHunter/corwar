# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcapers <dcapers@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/20 12:04:51 by dcapers           #+#    #+#              #
#    Updated: 2020/12/20 12:15:37 by dcapers          ###   ########.fr        #
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

ASM_LIST = asm_main.c \
			asm_utils.c \
			assemble.c \
			add_token.c \
			asm_errors.c \
			asm_utils2.c \
			parse_asm.c	\
			setup_info.c \
			setup_arg.c \
			create_label.c \
			resize_buff.c \
			buildup_code.c \
			buildup_binary.c \
			parse_str.c 
CORE_LIST = 

ASM_SRC_DIR = $(SRC_DIR)$(ASM_DIR)
CORE_SRC_DIR = $(SRC_DIR)$(CORE_DIR)

ASM_OBJ_DIR = $(OBJ_DIR)$(ASM_DIR)
CORE_OBJ_DIR = $(OBJ_DIR)$(CORE_DIR)

ASM_OBJ_LIST = $(patsubst %.c, %.o, $(ASM_LIST))
CORE_OBJ_LIST = $(patsubst %.c, %.o, $(CORE_LIST))

ASM_OBJ = $(addprefix $(ASM_OBJ_DIR),  $(ASM_OBJ_LIST))
CORE_OBJ = $(addprefix $(CORE_OBJ_DIR),  $(CORE_OBJ_LIST))

ASM_SRC = $(addprefix $(ASM_SRC_DIR), $(ASM_LIST))
CORE_SRC = $(addprefix $(CORE_SRC_DIR), $(CORE_LIST))

LIBFT_ALL		= $(addsuffix .all,$(LIBFT_DIR))
LIBFT_CLEAN	= $(addsuffix .clean,$(LIBFT_DIR))
LIBFT_FCLEAN	= $(addsuffix .fclean,$(LIBFT_DIR))

INCLUDES		= include/
INC_LIBFT	= $(addsuffix includes/,$(LIBFT_DIR))

ASM_HEADERS_LIST = asm.h errors.h
CORE_HEADERS_LIST = corewar.h errors.h

ASM_HEADERS = $(addprefix inc/, $(ASM_HEADERS_LIST))
CORE_HEADERS = $(addprefix inc/, $(CORE_HEADERS_LIST))

FLAGS = 

all: $(LIBFT_ALL) $(ASM_NAME) $(CORE_NAME) 

clean: $(LIBFT_CLEAN)
	@rm -rf $(ASM_OBJ_DIR) $(CORE_OBJ_DIR) $(OBJ_DIR)

fclean: $(LIBFT_FCLEAN) clean
	@rm -rf $(ASM_NAME) $(CORE_NAME)

re:		fclean all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(ASM_OBJ_DIR):
	@mkdir -p $(ASM_OBJ_DIR)

$(CORE_OBJ_DIR):
	@mkdir -p $(CORE_OBJ_DIR)

$(ASM_NAME): $(LIBFT) $(OBJ_DIR) $(ASM_OBJ_DIR) $(ASM_OBJ)
	@gcc $(FLAGS) $(ASM_INCLUDES) $(ASM_OBJ) $(LIBFT) -o $(ASM_NAME)
	@echo "\033[32m$(ASM_NAME) binary created\033[0m."

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