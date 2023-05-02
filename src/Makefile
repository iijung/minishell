# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:09:45 by minjungk          #+#    #+#              #
#    Updated: 2023/05/02 16:57:58 by jaemjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS		= -Wall -Wextra -Werror -MMD -MP -g

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
	environ/env_free.c \
	prompt/prompt.c \
	lexer/lexer.c \
	execute/run.c \
	builtin/builtin.c \
	builtin/pwd.c \
	builtin/cd.c \
	builtin/env.c \
	builtin/echo.c \
	builtin/exit.c \
	builtin/unset.c \
	builtin/export.c \
	parse/parse.c \

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
