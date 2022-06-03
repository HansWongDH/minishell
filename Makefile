# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 18:02:33 by wding-ha          #+#    #+#              #
#    Updated: 2022/06/04 03:23:26 by wding-ha         ###   ########.fr        #
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
CFLAGS			= -Wall -Wextra -Werror -fsanitize=address -g3
LFLAGS			= -L/usr/include -lreadline
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

##############
#sSOURCE FILE#
##############

S_SRCS			= $(SRC_DIR)main.c
S_LEX			= $(LEX_DIR)lex_init.c $(LEX_DIR)lex_utils.c $(LEX_DIR)lex_args.c $(LEX_DIR)lex_cmdlist.c
S_PARS			= $(PARS_DIR)pars_quote.c $(PARS_DIR)pars_cmdline.c $(PARS_DIR)pars_util.c $(PARS_DIR)pars_error.c
S_ENV			= $(ENV_DIR)env_expansion.c 
OBJS			= $(S_SRCS:.c=.o) $(S_LEX:.c=.o) $(S_PARS:.c=.o) $(S_ENV:.c=.o)

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