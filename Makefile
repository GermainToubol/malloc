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
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -fPIC
SHELL		:= /bin/bash

# List of all inclusions (.h and .a)
# -------------------------------------------------------------------------
INCLUDE_DIR	:= includes libft/includes
INCLUDES	:= $(addprefix -I,$(INCLUDE_DIR))

LIB_NAMES	:= ft
LIB_FILES	:= $(foreach l,$(LIB_NAMES),lib$l/lib$l.a)
EXT_LIB		:=
LIB			:= $(addprefix -Llib,$(LIB_NAMES)) $(addprefix -l,$(LIB_NAMES)	\
					$(EXT_LIB))

# List of all sources (.c)
# -------------------------------------------------------------------------
SRC_DIR		:= srcs
SRC_LST		:=	malloc.c													\
				$(addprefix mstack/,ft_mstack_init.c ft_mstack_extend.c		\
					ft_mstack_findaddr.c)									\
				$(addprefix gdata/,ft_gdata_init.c ft_gdata_free.c			\
					ft_gdata_alloc.c ft_gdata_set_area.c					\
					ft_gdata_findaddr.c)									\
				$(addprefix tree/,ft_tree_insert.c ft_tree_search.c 		\
					ft_node_init.c)
SRCS		:= $(addprefix $(SRC_DIR)/,$(SRC_LST))

# List of all object files (.o)
# -------------------------------------------------------------------------
ifeq (,$(filter test, $(MAKECMDGOALS)))
	OBJ_DIR	:= objs
	CFLAGS	+= -fvisibility=hidden
	HOSTTYPE	?= $(shell uname -m)_$(shell uname -s)
	IS_TEST := false
else
	OBJ_DIR	:= objs.test
	CFLAGS += -g3
	HOSTTYPE	?= $(shell uname -m)_$(shell uname -s)
	HOSTTYPE 	:= $(HOSTTYPE)_test
	IS_TEST := true
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
#			@if [ "$(IS_TEST)" = false ]; then strip -x $(GENERIC) 			\
#				&& echo "striping the symbols"; fi

$(NAME):	$(OBJS)
			$(CC) $(INCLUDES) $^ -shared -o $@

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c start_compiling
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(OBJ_DIR)/%.d: $(SRC_DIR)/%.c start_deps
			@mkdir -p $(dir $@)
			$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDES) $< > $@

.PHONY:		clean
clean:
			$(RM) $(OBJS)

.PHONY:		dclean
dclean:
			$(RM) $(DEPS)


.PHONY:		fclean
fclean:		clean dclean
			$(RM) $(NAME) $(GENERIC)
			@rmdir -p --ignore-fail-on-non-empty $(dir $(OBJS)) 2> /dev/null	\
				|| exit 0

.PHONY:		re
re:			fclean all

.PHONY: 	test
test:		all
			pytest

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
