# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:09:45 by minjungk          #+#    #+#              #
#    Updated: 2023/03/07 06:43:26 by jaemjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS		= -Wall -Wextra -Werror -MMD -MP -O3

CPPFLAGS	+= -I./util
CPPFLAGS	+= -I./environ
CPPFLAGS	+= -I./prompt
CPPFLAGS	+= -I./builtin
CPPFLAGS	+= -I./lexer
CPPFLAGS	+= -I./parse

CPPFLAGS	+= -I../lib/libft
LDFLAGS		+= -L../lib/libft
LDLIBS		+= -lft

CPPFLAGS	+= -I../external/include/ncurses
CPPFLAGS	+= -I../external/include/readline
LDFLAGS		+= -L../external/lib
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
	util/ft_strndup.c \
	environ/environ.c \
	environ/env_init.c \
	prompt/prompt.c \
	execute/run.c \
	builtin/builtin.c \
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
	parse/lr_action_func.c \
	parse/clear_tree.c \
	parse/lr_util.c 
	builtin/cd.c \
	builtin/env.c \
	builtin/exit.c \

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
