# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 07:31:36 by minjungk          #+#    #+#              #
#    Updated: 2023/02/27 09:34:36 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

RM		= rm -rf
LN_S	= ln -s
MKDIR	= mkdir -p
RMDIR	= rmdir -p

# **************************************************************************** #
# docker
# **************************************************************************** #
DKR = docker
DKR_GOINFRE_PATH	= $(HOME)/goinfre/docker
DKR_CONTAINERS_PATH	= $(HOM#)/Library/Containers/com.docker.docker

DKR_RUN	= $(DKR) run
DKR_OPT	+= --interactive			# Keep STDIN open even if not attched
DKR_OPT	+= --tty					# Allocate a pseudo-TTY
DKR_OPT	+= --rm						# Automatically remove ther container exits
DKR_OPT	+= --init					# Run an init inside the container
DKR_OPT	+= -v "$(HOME):/$(USER)"	# Bind mount a volume
DKR_IMG	= nloomans/codam
DKR_CMD	= sh -c "cd /$(USER); bash"

init_docker:
	$(MKDIR) $(DKR_GOINFRE_PATH)
	$(RM) $(DKR_CONTAINERS_PATH)
	$(LN_S) $(DKR_GOINFRE_PATH) $(DKR_CONTAINERS_PATH)

run_docker:
	$(DKR_RUN) $(DKR_OPT) $(DKR_IMG) $(DKR_CMD)

# **************************************************************************** #
# compile
# **************************************************************************** #
CFLAGS += -Wall -Wextra -Werror -MMD -MP
CFLAGS += -pedantic -Weverything
CFLAGS += -O0 -g

ifeq ($(shell uname), Darwin)
	CFLAGS += -fsanitize=address,undefined
	LDFLAGS += -fsanitize=address,undefined
endif

VALGRIND_OPT	+= --trace-children=yes
VALGRIND_OPT	+= --track-fds=all
MEMCHECK_OPT	+= --leak-check=full
MEMCHECK_OPT	+= --show-leak-kinds=all
MEMCHECK_OPT	+= --undef-value-errors=yes
MEMCHECK_OPT	+= --track-origins=yes
MEMCHECK_OPT	+= --keep-stacktraces=alloc-and-free

valgrind:		# make valgrind program="./test"
	valgrind $(VALGRIND_OPT) $(MEMCHECK_OPT) $(program)
