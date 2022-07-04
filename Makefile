# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 18:02:33 by wding-ha          #+#    #+#              #
#    Updated: 2022/07/04 13:57:09 by wding-ha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########
#FILE NAME#
###########

NAME			= minishell

#######
#FLAGS#
#######

CC				= gcc -Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS			= -I/usr/local/opt/readline/include
LFLAGS			= -L/usr/include -L/usr/local/opt/readline/lib -lreadline
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
EXE_DIR			= src/exec/
RED_DIR			= src/redir/
SIG_DIR			= src/signal/
MAIN			= $(SRC_DIR)main.c
##############
#sSOURCE FILE#
##############

S_SRCS			= $(addprefix $(LEX_DIR), lexer_init.c token_utils.c token_init.c cmdlist_init.c cmdlist_utils.c) \
				  $(addprefix $(PARS_DIR), pars_quote.c pars_util.c pars_cmd.c pars_child.c) \
				  $(addprefix $(ENV_DIR), env_expansion.c env_get.c env_build.c) \
				  $(addprefix $(ERR_DIR), error_msg.c free_memory.c) \
				  $(addprefix $(BIN_DIR), bin_export.c bin_echo.c bin_env.c bin_unset.c bin_exit.c bin_pwd.c bin_cd.c) \
				  $(addprefix $(EXE_DIR), executor.c)\
				  $(addprefix $(RED_DIR), red_dup.c red_heredoc.c)\
				  $(addprefix $(SIG_DIR), signal_handlers.c)
OBJS			= $(S_SRCS:.c=.o) 
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