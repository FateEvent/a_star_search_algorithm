# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/07/26 15:32:22 by faventur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#		( ͡° ͜ʖ ͡°)			COMPILATION			( ͡° ͜ʖ ͡°)

NAME = a_star
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LINKS = -I./includes
SRC_PATH = srcs/
OBJ_PATH = bin/
C_EXTENSION = .c

#		눈_눈			SOURCES			눈_눈

MAIN_PATH	=	
MAIN_FILES 	= 	a_star_algo
SRCS_FILES	+=	$(addprefix $(MAIN_PATH), $(MAIN_FILES))

STACK_PATH	=	stacks/
STACK_FILES =	ft_stacknew ft_newnode ft_stackadd_top \
				ft_stackadd_bottom ft_stackdelone ft_stackclear \
				ft_stackinsert ft_stackiter ft_stacksize ft_stacksort \
				ft_stackiter_if ft_stack_remove_if ft_stacklast
SRCS_FILES	+=	$(addprefix $(STACK_PATH), $(STACK_FILES))

SRCS_FILES_EXT 		+= 	$(addsuffix $(C_EXTENSION), $(SRCS_FILES))
SRCS 				+= 	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))
OBJS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:c=o))

#		(҂◡_◡)			UTILS			(҂◡_◡)

RM = rm -rf

#		(｡◕‿◕｡)			COLORS			(｡◕‿◕｡)

NONE = \033[0m
HIRED = \033[31m
HIGREEN = \033[92m
HIBLUE = \033[94m
CURSIVE = \033[3m

#		( ಠ ʖ̯ ಠ)		RULES			( ಠ ʖ̯ ಠ)

all: $(NAME)

$(NAME):  $(OBJS)
	@echo "$(HIRED)Compiling...$(NONE)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

.c.o:
	@$(CC) $(FLAGS) -c ${LINKS} $< -o ${<:.c=.o} 


$(OBJ_PATH)%.o: $(SRC_PATH)%.c 
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $(LINKS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.phony: all clean fclean re
