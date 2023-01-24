# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:09:45 by minjungk          #+#    #+#              #
#    Updated: 2023/01/24 23:37:00 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

CFLAGS		= -Wall -Wextra -Werror -MMD -MP -O3

LDLIBS		+= -lncurses
LDLIBS		+= -lreadline

# **************************************************************************** #
MINISHELL = minishell

MINISHELL_SRCS = \
	minishell.c \

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
