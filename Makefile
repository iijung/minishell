# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:02:03 by minjungk          #+#    #+#              #
#    Updated: 2023/01/24 23:31:41 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

MINISHELL = minishell

all bonus clean fclean re:
	$(MAKE) -C lib $@
	$(MAKE) -C src $@

$(MINISHELL):
	$(MAKE) -C lib
	$(MAKE) -C src

.PHONY: all clean fclean re bonus $(MINISHELL)
