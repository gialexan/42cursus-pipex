# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 17:56:12 by gialexan          #+#    #+#              #
#    Updated: 2023/09/25 15:40:50 by gialexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                                PIPEX                                       ##
################################################################################

RESET := \033[0m
CYAN  := \033[1;36m
CHECK := \342\234\224
LOG   := printf "[$(CYAN)$(CHECK)$(RESET)] %s\n"

NAME := 			pipex

NAME_BONUS :=		pipex_bonus

################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR		:= obj

LIBFT_DIR   := libft

SRC_FILES	:= 	pipex.c cmd.c destroy.c exec.c

BONUS_FILES	:=	pipex_bonus.c cmd_bonus.c destroy_bonus.c exec_bonus.c

OBJS 		:= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

OBJS_BONUS	:= $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))

LIBFT		:= $(LIBFT_DIR)/libft.a

all:		$(NAME)

################################################################################
##                                 COMPILATION                                ##
################################################################################

CFLAGS  := -Wall -Werror -Wextra $(addprefix -I,$(LIBFT_DIR))

$(NAME): $(OBJS) | $(LIBFT)
	@$(LOG) "Building $@"
	@$(CC) $^ $(LIBFT) -o $@

bonus: $(OBJS_BONUS) | $(LIBFT)
	@$(LOG) "Building $@"
	@$(CC) $^ $(LIBFT) -o $(NAME_BONUS)

$(OBJ_DIR)/%.o: src_bonus/%.c | $(OBJ_DIR)
	@$(LOG) "Compiling $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@$(LOG) "Compiling $(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating objects directory"
	@mkdir $@

$(LIBFT):
	@$(LOG) "Building $(notdir $@)"
	@make bonus -C $(LIBFT_DIR) --no-print-directory --silent

clean:
	@$(RM) -r $(OBJS)
	@$(LOG) "Removing objects"
	@$(RM) -r $(OBJ_DIR)
	@$(LOG) "Removing objects directory"
	@$(RM) -r $(NAME)
	@$(LOG) "Removing $(NAME)"
	@$(RM) -r $(NAME_BONUS)
	@$(LOG) "Removing $(NAME_BONUS)"

fclean: clean
	@$(LOG) "Removing libft"
	@make fclean -C $(LIBFT_DIR) --no-print-directory --silent

re:					fclean all

.PHONY:				all clean fclean re libft
