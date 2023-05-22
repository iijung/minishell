# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:05:51 by minjungk          #+#    #+#              #
#    Updated: 2023/05/22 17:21:02 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

all bonus:
	$(MAKE) readline_all

clean:
	$(MAKE) readline_clean

fclean:
	$(MAKE) readline_fclean

re:
	$(MAKE) readline_re

.PHONY: all clean fclean re bonus

# **************************************************************************** #
READLINE_VERSION	= 8.2
READLINE_DIR		= readline-$(READLINE_VERSION)
READLINE_LIB		= libreadline.a

readline_all: $(READLINE_LIB)
$(READLINE_LIB):
	@if [ ! -f $(READLINE_DIR)/Makefile ]; then \
		cd $(READLINE_DIR); \
		./configure \
			--prefix=$(abspath .) \
			--libdir=$(abspath ./lib) \
			--includedir=$(abspath ./include/readline); \
	fi
	cd $(READLINE_DIR); $(MAKE)
	cd $(READLINE_DIR); $(MAKE) install

readline_clean:
	@if [ -f $(READLINE_DIR)/Makefile ]; then \
		cd $(READLINE_DIR); $(MAKE) clean; \
	fi

readline_fclean:
	@if [ -f $(READLINE_DIR)/Makefile ]; then \
		cd $(READLINE_DIR); $(MAKE) uninstall; \
		cd $(READLINE_DIR); $(MAKE) distclean; \
	fi

readline_re:
	$(MAKE) readline_fclean
	$(MAKE) readline_all
