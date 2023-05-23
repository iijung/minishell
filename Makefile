# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:02:03 by minjungk          #+#    #+#              #
#    Updated: 2023/05/22 17:28:04 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

MINISHELL = minishell

all bonus $(MINISHELL):
	$(MAKE) -C external
	$(MAKE) -C lib
	$(MAKE) -C src
	cp ./src/$(MINISHELL) $(MINISHELL)

re: fclean
	$(MAKE) all

clean:
	$(MAKE) -C external clean
	$(MAKE) -C lib clean
	$(MAKE) -C src clean

fclean:
	$(MAKE) -C external fclean
	$(MAKE) -C lib fclean
	$(MAKE) -C src fclean
	$(RM) $(MINISHELL)

.PHONY: all clean fclean re bonus $(MINISHELL)
