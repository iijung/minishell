# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaemjeon <jaemjeon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:09:45 by minjungk          #+#    #+#              #
#    Updated: 2023/02/13 22:18:27 by jaemjeon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS		= -Wall -Wextra -Werror -MMD -MP -O3

CPPFLAGS	+= -I./
CPPFLAGS	+= -I./prompt
CPPFLAGS	+= -I./lexer
CPPFLAGS	+= -I./signal

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
	prompt/termset.c \
	lexer/lexer.c \
	builtin/pwd.c \
	signal/signal.c \

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
