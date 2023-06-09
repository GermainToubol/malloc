#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/13 19:14:11 by gtoubol           #+#    #+#              #
#    Updated: 2023/02/13 19:14:11 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Compilation options
# -------------------------------------------------------------------------
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -fPIC
SHELL		:= /bin/bash

# List of all inclusions (.h and .a)
# -------------------------------------------------------------------------
INCLUDE_DIR	:= includes libft/includes
INCLUDES	:= $(addprefix -I,$(INCLUDE_DIR))

LIB_NAMES	:= ft
LIB_FILES	:= $(foreach l,$(LIB_NAMES),lib$l/lib$l.so)
EXT_LIB		:= pthread
LIB			:= $(addprefix -Llib,$(LIB_NAMES)) $(addprefix -l,$(LIB_NAMES)	\
					$(EXT_LIB))

# List of all sources (.c)
# -------------------------------------------------------------------------
SRC_DIR		:= srcs
SRC_LST		:= malloc.c free.c realloc.c generic.c							\
				$(addprefix mstack/,ft_mstack_init.c ft_mstack_extend.c		\
					ft_mstack_findaddr.c ft_mstack_unmap.c)					\
				$(addprefix gdata/,ft_gdata_init.c ft_gdata_free.c			\
					ft_gdata_alloc.c ft_gdata_set_area.c					\
					ft_gdata_findaddr.c)									\
				$(addprefix tree/,ft_tree_insert.c ft_tree_search.c 		\
					ft_node_init.c)											\
				$(addprefix dump/,show_alloc_mem.c show_historics.c			\
					show_alloc_mem_ex.c)									\
				$(addprefix heap/,ft_heap_swap_nodes.c ft_queue_push.c		\
					ft_queue_pop.c)											\
				$(addprefix tiny/,ft_tiny_init.c ft_tiny_alloc.c			\
					ft_tiny_free.c ft_tiny_delete.c)						\
				$(addprefix small/,ft_small_init.c ft_small_alloc.c			\
					ft_small_free.c ft_small_delete.c)
SRCS		:= $(addprefix $(SRC_DIR)/,$(SRC_LST))

# List of all object files (.o)
# -------------------------------------------------------------------------
ifeq (,$(filter test, $(MAKECMDGOALS)))
	CFLAGS	+= -fvisibility=hidden
	HOSTTYPE	?= $(shell uname -m)_$(shell uname -s)
	OBJ_DIR	:= objs/objs.$(HOSTTYPE)
	IS_TEST := false
else
	CFLAGS += -g3
	HOSTTYPE	?= $(shell uname -m)_$(shell uname -s)
	HOSTTYPE 	:= $(HOSTTYPE)_test
	OBJ_DIR	:= objs/objs.test
	IS_TEST := true
endif

ifeq (bonus, $(filter bonus, $(MAKECMDGOALS)))
	CFLAGS += -DBONUS
	HOSTTYPE := $(HOSTTYPE)_bonus
	OBJ_DIR	:= $(OBJ_DIR).bonus
endif


GENERIC		:= libft_malloc.so
NAME		:= libft_malloc_$(HOSTTYPE).so

OBJ_LST		:= $(SRC_LST:.c=.o)
OBJS		:= $(addprefix $(OBJ_DIR)/,$(OBJ_LST))

DEPS		:= $(OBJS:.o=.d)

# Rules
# -------------------------------------------------------------------------
.PHONY:		all
all:		test-generic $(GENERIC)

.PHONY: 	test_generic
test-generic:
			@if [ ! $(GENERIC) -ef $(NAME) ]; then							\
				$(RM) -v $(GENERIC);										\
			fi

$(GENERIC): $(NAME)
			$(RM) $(GENERIC)
			ln -s $(NAME) $(GENERIC)
			@if [ "$(IS_TEST)" = false ]; then strip -x $(GENERIC) 			\
				&& echo "striping the symbols"; fi

$(NAME):	$(OBJS) $(LIB_FILES)
			$(CC) $(INCLUDES) $(OBJS) $(CFLAGS) -shared -o $@ -lft -L./libft -Wl,-rpath=$(shell pwd)/libft

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c start_compiling
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c start_deps
			@mkdir -p $(dir $@)
			$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDES) $< > $@

.PHONY:		clean
clean:
			@$(RM) -rv objs


.PHONY:		fclean
fclean:		clean
			$(RM) $(NAME) $(GENERIC)
			@rmdir -p --ignore-fail-on-non-empty $(dir $(OBJS)) 2> /dev/null	\
				|| exit 0

.PHONY:		re
re:			fclean all

.PHONY: 	test
test:		all
			pytest

.PHONY:		bonus
bonus:		all

# Documentation
# -------------------------------------------------------------------------
.PHONY:		doc
doc:
			@mkdir -p doc
			doxygen Doxyfile

.PHONY:		docclean
docclean:
			rm -rf doc

# Libraries
# -------------------------------------------------------------------------
%.a:		build_libs
			@echo -e "$(_GREEN)$(dir $@): make$(_NO_COLOR)"
			$(MAKE) --no-print-directory -C $(dir $@)

%.so:		build_libs
			@echo -e "$(_GREEN)$(dir $@): make$(_NO_COLOR)"
			$(MAKE) --no-print-directory -C $(dir $@) shared

# Parameters
# -------------------------------------------------------------------------
_GREY		= \033[30m
_RED		= \033[31m
_GREEN		= \033[32m
_YELLOW		= \033[33m
_BLUE		= \033[34m
_PURPLE		= \033[35m
_CYAN		= \033[36m
_WHITE		= \033[37m
_NO_COLOR	= \033[0m

.INTERMEDIATE:	start_deps
start_deps:
			@echo -e "$(_GREEN)Build dependencies$(_NO_COLOR)"

.INTERMEDIATE:	build_libs
build_libs:
			@echo ''
			@echo -e "$(_PURPLE)Build libraries$(_NO_COLOR)"

.INTERMEDIATE:	start_compiling
start_compiling:
			@echo ''
			@echo -e "$(_GREEN)Start Compiling $(_NO_COLOR)"

.INTERMEDIATE:	start_link
start_link:
			@echo ""
			@echo -e "$(_BLUE)Linkage $(NAME)$(_NO_COLOR)"

.INTERMEDIATE:	start_watch
start_watch:
			@echo -e "$(_PURPLE)=== Start watch mode ===$(_NO_COLOR)"

-include $(DEPS)
