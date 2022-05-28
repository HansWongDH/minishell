# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wding-ha <wding-ha@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/12 18:02:33 by wding-ha          #+#    #+#              #
#    Updated: 2022/05/28 15:32:07 by wding-ha         ###   ########.fr        #
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

##############
#sSOURCE FILE#
##############

S_SRCS			= $(SRC_DIR)main.c
S_LEX			= $(LEX_DIR)lex_init.c $(LEX_DIR)lex_utils.c $(LEX_DIR)lex_args.c $(LEX_DIR)lex_cmdlist.c
OBJS			= $(S_SRCS:.c=.o) $(S_LEX:.c=.o)

##########
#COMMANDS#
##########

all:			$(NAME) $(B_NAME)

$(NAME):		$(OBJS)
	@make re -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(LFLAGS) $(INC) -o $(NAME) $(MAIN) $(OBJS) $(LIB)
	
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