# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaemjeon <jaemjeon@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:09:45 by minjungk          #+#    #+#              #
#    Updated: 2023/05/18 22:48:02 by minjungk         ###   ########.fr        #
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
CPPFLAGS	+= -I./expand
CPPFLAGS	+= -I./execute

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
	lexer/get_lexeme.c \
	lexer/skip_lexeme.c \
	lexer/check_lexeme.c \
	expand/get_heredoc.c \
	expand/get_wildcard.c \
	execute/executor.c \
	execute/run_pipex.c \
	execute/set_pipex.c \
	execute/init_pipex.c \
	execute/redirect.c \
	execute/read_redirect.c \
	builtin/builtin.c \
	builtin/pwd.c \
	builtin/cd.c \
	builtin/env.c \
	builtin/echo.c \
	builtin/exit.c \
	builtin/unset.c \
	builtin/export.c \
	parse/parse.c \
	parse/syntax.c \
	parse/parse_util.c \
	parse/parse_inner_util.c \
	parse/parse_inner_util2.c \
	parse/parse_inner_syntax.c \
	parse/parse_inner_getter.c \

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
