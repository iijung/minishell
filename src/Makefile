# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:09:45 by minjungk          #+#    #+#              #
#    Updated: 2023/03/07 03:04:15 by jaemjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS		= -Wall -Wextra -Werror -MMD -MP -O3

CPPFLAGS	+= -I./prompt
CPPFLAGS	+= -I./lexer
CPPFLAGS	+= -I./parse

CPPFLAGS	+= -I../lib/libft
CPPFLAGS	+= -I../lib/readline
LDFLAGS		+= -L../lib/libft
LDFLAGS		+= -L../lib/readline
LDLIBS		+= -lft

LDLIBS		+= -lncurses
LDLIBS		+= -lreadline

ifdef DEBUG
CPPFLAGS	+= -g -DDEBUG
endif

# **************************************************************************** #
MINISHELL = minishell

MINISHELL_SRCS = \
	minishell.c \
	util/ft_debug.c \
	util/ft_assert.c \
	prompt/prompt.c \
	lexer/lexer.c \
	lexer/lexer_util.c \
	builtin/pwd.c \
	parse/parse.c \
	parse/lr_state01.c \
	parse/lr_state02.c \
	parse/lr_state03.c \
	parse/lr_state04.c \
	parse/lr_state05.c \
	parse/lr_reduce01.c \
	parse/lr_reduce02.c \
	parse/lr_reduce03.c \
	parse/lr_stack_adt.c \
	parse/lr_action_func.c

MINISHELL_OBJS := $(MINISHELL_SRCS:.c=.o)
MINISHELL_DEPS := $(MINISHELL_SRCS:.c=.d)
-include $(MINISHELL_DEPS)

$(MINISHELL): $(MINISHELL_OBJS)

# **************************************************************************** #

all: $(MINISHELL)
bonus: $(MINISHELL)

clean:
	$(RM) $(MINISHELL_OBJS) $(MINISHELL_DEPS)

fclean: clean
	$(RM) $(MINISHELL)

re: fclean
	$(MAKE) $(if $(filter bonus,$(MAKECMDGOALS)), bonus, all)

.PHONY: all clean fclean re bonus
