# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echai <echai@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 18:02:33 by wding-ha          #+#    #+#              #
#    Updated: 2022/06/22 13:59:27 by echai            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########
#FILE NAME#
###########

NAME			= minishell

#######
#FLAGS#
#######

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -fsanitize=address -g3 -I/usr/local/opt/readline/include
LFLAGS			= -L/usr/local/opt/readline/lib -lreadline
RM				= rm -f

##################
#PATH AND LIBRARY#
##################

INC				= -Iinclude -I$(LIBFT_DIR)
LIBFT_DIR		= libs/libft
LIB				= -L$(LIBFT_DIR) -lft
SRC_DIR			= src/
LEX_DIR			= src/lexer/
PARS_DIR		= src/parser/
ENV_DIR			= src/env/
ERR_DIR			= src/error/
BIN_DIR			= src/built-in/
SIG_DIR			= src/signal/

##############
#sSOURCE FILE#
##############

S_SRCS			= $(SRC_DIR)main.c
S_LEX			= $(LEX_DIR)lexer_init.c $(LEX_DIR)token_utils.c \
				  $(LEX_DIR)token_init.c $(LEX_DIR)cmdlist_init.c $(LEX_DIR)cmdlist_utils.c 
S_PARS			= $(PARS_DIR)pars_quote.c $(PARS_DIR)pars_util.c $(PARS_DIR)pars_cmd.c
S_ENV			= $(ENV_DIR)env_expansion.c $(ENV_DIR)env_get.c $(ENV_DIR)env_build.c
S_ERR			= $(ERR_DIR)error_msg.c $(ERR_DIR)free_memory.c
S_BIN			= $(BIN_DIR)bin_export.c $(BIN_DIR)bin_echo.c $(BIN_DIR)bin_env.c $(BIN_DIR)bin_unset.c \
				  $(BIN_DIR)bin_exit.c $(BIN_DIR)bin_pwd.c $(BIN_DIR)bin_cd.c
S_SIG			= $(SIG_DIR)signal_handlers.c
OBJS			= $(S_SRCS:.c=.o) $(S_LEX:.c=.o) $(S_PARS:.c=.o) $(S_ENV:.c=.o) $(S_ERR:.c=.o) $(S_BIN:.c=.o) $(S_SIG:.c=.o)

##########
#COMMANDS#
##########

all:			$(NAME) $(B_NAME)

$(NAME):		$(OBJS)
	@make re -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INC) -o $(NAME) $(MAIN) $(OBJS) $(LIB) $(LFLAGS) 
	
%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
clean:
	@$(RM) $(OBJS) $(B_OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME) $(B_NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re