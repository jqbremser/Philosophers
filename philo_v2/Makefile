# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbremser <jbremser@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 13:29:28 by jbremser          #+#    #+#              #
#    Updated: 2024/08/02 14:30:58 by jbremser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	philo

FLAGS 		=	-Wall -Werror -Wextra -g
FILES		=	prime_time_dine_time.c \
				the_help.c \
				init.c \
				kronos.c \
				routine.c \
				threads.c \
				locks.c
SRCDIR		=	srcs
OBJDIR		=	objs

HEADER		=	symposium.h

SRCS		=	$(addprefix $(SRCDIR)/, $(FILES))
OBJS		=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

ANSI_CYAN	:= \032[0;36m
ANSI_BLUE	:= \032[0;34m
ANSI_RED	:= \032[31m
ANSI_RESET	:= \032[0m

all:		$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER)
			@mkdir -p $(OBJDIR)
			@cc $(FLAGS) -o $@ -c $<

$(NAME):	$(OBJS) 
			@cc $(OBJS) -o $(NAME)
			@echo "$(ANSI_CYAN) Compilation Complete: $(NAME) $(ANSI_RESET)"

clean:		
			@rm -rf $(OBJDIR)
			@echo "$(ANSI_RED) Objects cleaned$(ANSI_RESET)"

fclean:		clean
			@rm -rf $(NAME)
			@echo "$(ANSI_RED) Executable $(NAME) removed$(ANSI_RESET)"

re:			fclean all

.PHONY:		all clean fclean re

