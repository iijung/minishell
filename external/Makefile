# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 23:05:51 by minjungk          #+#    #+#              #
#    Updated: 2023/02/20 23:04:50 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

all bonus:
	$(MAKE) ncurses_all
	$(MAKE) readline_all

clean:
	$(MAKE) ncurses_clean
	$(MAKE) readline_clean

fclean:
	$(MAKE) ncurses_fclean
	$(MAKE) readline_fclean

re:
	$(MAKE) ncurses_re
	$(MAKE) readline_re

.PHONY: all clean fclean re bonus

# **************************************************************************** #
NCURSES_VERSION	= 6.4
NCURSES_DIR		= ncurses-$(NCURSES_VERSION)
NCURSES_LIB		= libncurses.a

ncurses_all: $(NCURSES_LIB)
$(NCURSES_LIB):
	@if [ ! -f $(NCURSES_DIR)/Makefile ]; then \
		cd $(NCURSES_DIR); \
		./configure \
			--with-termlib \
			--without-debug \
			--without-manpages \
			--without-progs \
			--without-tack \
			--without-tests \
			--without-shared \
			--disable-db-install \
			--prefix=$(abspath .) \
			--libdir=$(abspath ./lib) \
			--includedir=$(abspath ./include); \
	fi
	cd $(NCURSES_DIR); $(MAKE)
	cd $(NCURSES_DIR); $(MAKE) install

ncurses_clean:
	@if [ -f $(NCURSES_DIR)/Makefile ]; then \
		cd $(NCURSES_DIR); $(MAKE) clean; \
	fi

ncurses_fclean:
	@if [ -f $(NCURSES_DIR)/Makefile ]; then \
		cd $(NCURSES_DIR); $(MAKE) uninstall; \
		cd $(NCURSES_DIR); $(MAKE) distclean; \
	fi

ncurses_re:
	$(MAKE) ncurses_fclean
	$(MAKE) ncurses_all

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
