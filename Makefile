# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfilloux <lfilloux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 11:34:35 by aleferra          #+#    #+#              #
#    Updated: 2022/05/27 13:20:57 by lfilloux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = srcs
SRC_FILES = main.c					\
			signaux.c				\
			tokens.c				\
			free.c					\
			free_app.c				\
			free_env.c				\
			init/init_env.c			\
			init/init_cmd.c			\
			init/init_chain.c 		\
			app/init_app.c			\
			app/start_app.c			\
			app/pipe.c				\
			app/lexer.c				\
			app/expand.c			\
			app/syntaxer.c			\
			parse/parse.c			\
			parse/token.c			\
			parse/quote.c			\
			parse/arg.c				\
			parse/name.c			\
			parse/catch_error.c		\
			parse/clean_quote.c		\
			builtins/echo.c 		\
			builtins/env.c 			\
			builtins/cd.c 			\
			builtins/exit.c 		\
			builtins/pwd.c 			\
			builtins/dispatcher.c	\
			builtins/unset.c		\
			builtins/export.c		\
			redirection/in.c		\
			redirection/heredoc.c	\
			redirection/out.c		\
			redirection/utils_cmd.c	\
			utils/paths.c			\
			utils/in.c				\
			utils/out.c				\
			utils/heredoc.c			\
			utils/native_paths.c	\
			utils/errors.c			\
			utils/reset_str.c		\
			utils/tab_env.c			\
			utils/redirection.c		\
			utils/permissions.c		\
			utils/export.c			\
			utils/arg.c				\
			utils/nu.c				\

RL_LIB = -L$(shell brew --prefix readline)/lib
RL_INC = -I$(shell brew --prefix readline)/include
LIB_EX = ./libft/libft.a
OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:.c=.o)
INCLUDE_DIRS = libft
DEPENDENCIES = includes/minishell.h includes/error.h includes/structure.h includes/enums.h libft/libft.a Makefile
LIB_DIRS = libft
LIBS = ft readline
CC = gcc
C_FLAGS = $(addprefix -I, $(INCLUDE_DIRS)) -Wall -Wextra -Werror #-fsanitize=address

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPENDENCIES)
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(RL_INC) -c $< -o $@

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))
	$(CC) $(C_FLAGS) $(RL_INC) $(RL_LIB) -lreadline $(addprefix $(OBJ_DIR)/, $(OBJ_FILES)) $(addprefix -L, $(LIB_DIRS)) $(addprefix -l, $(LIBS)) $(RL_INC) -o $(NAME)

libft:
	@make -C libft

$(LIB_EX): libft

clean:
	rm -rf $(OBJ_DIR)

fclean_libs:
	make -C libft fclean

fclean: clean fclean_libs
	rm -f $(NAME)

re: fclean all

.PHONY: re all libft clean fclean fclean_libs