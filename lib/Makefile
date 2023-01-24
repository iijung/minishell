# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:05:51 by minjungk          #+#    #+#              #
#    Updated: 2023/01/24 23:11:05 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

MAKEFLAGS	= -j 8

LIBS		=	libft/libft.a

all bonus clean fclean re:
	@for dir in $(dir $(LIBS)); do \
		$(MAKE) -C $$dir $@; \
	done

.PHONY: all clean fclean re bonus
