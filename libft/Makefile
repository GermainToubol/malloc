#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 16:23:23 by gtoubol           #+#    #+#              #
#    Updated: 2022/12/20 16:23:23 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NSRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c 	\
		ft_strlen.c ft_atoi.c ft_toupper.c ft_tolower.c ft_memset.c			\
		ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c		\
		ft_strchr.c ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c 		\
		ft_memcmp.c

SRCS =	$(NSRCS) ft_calloc.c ft_printf.c ft_free_split.c ft_itoa.c 			\
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c		\
		ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c 		\
		ft_printf.c ft_printf_char.c ft_printf_formatify.c ft_printf_hex.c	\
		ft_printf_hex_base.c ft_printf_hex_caps.c ft_printf_int.c 			\
		ft_printf_long_hex.c ft_printf_padding.c ft_printf_percent.c		\
		ft_printf_precision.c ft_printf_ptr.c ft_printf_str.c 				\
		ft_printf_unsigned.c ft_printf_write.c ft_putchar_fd.c 				\
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strdup.c\
		ft_striteri.c ft_strjoin.c ft_strmapi.c ft_strnstr.c ft_substr.c	\
		ft_isspace.c ft_atoll.c ft_fprintf.c

OBJS = $(addprefix $(OBJS_D)/,$(SRCS:.c=.o))
SOBJS= $(OBJS:.o=.s.o)
TEST = $(addprefix $(TEST_D)/,$(NSRCS:.c=.test))

SRCS_D = ./srcs
INCL_D = ./includes
OBJS_D = ./objs
TEST_D = ./tests

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = $(addprefix -I,$(INCL_D))

NAME = libft.a
SHARED = $(NAME:.a=.so)

all: $(NAME)

shared: $(SHARED)

$(SHARED): $(SOBJS)
	$(CC) $(CLFAGS) $(INCLUDES) -shared -o $@ $^

$(NAME): $(OBJS)
	ar rcs $@ $^

$(OBJS_D)/%.o: $(SRCS_D)/%.c Makefile
	@if [ ! -d $(dir $@) ]; then				\
		mkdir -p $(dir $@);						\
	fi
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_D)/%.s.o: $(SRCS_D)/%.c Makefile
	@if [ ! -d $(dir $@) ]; then				\
		mkdir -p $(dir $@);						\
	fi
	$(CC) $(CFLAGS) -fPIC $(INCLUDES) -c $< -o $@

%.test: %.c $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) $< -L. -lft -lbsd -o $@

clean:
	$(RM) $(OBJS) $(SOBJS)
	$(RM) -d $(OBJS_D)

tclean:
	$(RM) $(TEST)

fclean: clean tclean
	$(RM) $(NAME) $(SHARED)

re: fclean all

test: $(TEST)
	@for file in $(TEST); do	\
		$$file;					\
	done;

.PHONY: all clean fclean re test shared tclean
