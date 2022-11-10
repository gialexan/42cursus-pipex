# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 17:56:12 by gialexan          #+#    #+#              #
#    Updated: 2022/11/10 18:06:55 by gialexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 				pipex

NAME_BONUS =		pipex_bonus

SRC_FILE = 			pipex.c cmd.c destroy.c exec.c

SRC_FILE_BONUS =	pipex_bonus.c cmd_bonus.c destroy_bonus.c exec_bonus.c

SRC_DIR = 			src

SRC_DIR_BONUS =		src_bonus

LIBFT_DIR = 		libft

SRC = 				$(addprefix $(SRC_DIR)/, $(SRC_FILE))

SRC_BONUS =			$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILE_BONUS))

SRC_OBJ = 			$(SRC:.c=.o)

SRC_OBJ_BONUS =		$(SRC_BONUS:.c=.o)

LIBFT = 			./libft/libft.a

RM = 				rm -f

CFLAGS = 			-Wall -Wextra -Werror -g

CC = 				cc $(CFLAGS)

all:	$(NAME)

bonus:	$(NAME_BONUS)

$(NAME):			$(LIBFT) $(SRC_OBJ)
					$(CC) $(SRC_OBJ) $(LIBFT) -o $(NAME)

$(NAME_BONUS):		$(LIBFT) $(SRC_OBJ_BONUS)
					$(CC) $(SRC_OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(LIBFT):
					$(MAKE) -C $(LIBFT_DIR)

clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) $(SRC_OBJ)
					$(RM) $(SRC_OBJ_BONUS)
					
fclean:				clean
					$(MAKE) fclean -C $(LIBFT_DIR)
					$(RM) $(NAME)
					$(RM) $(NAME_BONUS)

re:					fclean all

test1:				$(NAME)
					< file1 ls -la | wc -l > file2
					valgrind ./pipex infile "ls -la" "wc -l" outfile
					
test2:				$(NAME)
					< file1 ls -l | wc -l > file2
					valgrind ./pipex infile "ls -l" "wc -l" outfile
					
test3:				$(NAME)
					< file1 grep a1 | wc -w > file2
					valgrind ./pipex infile "grep a1" "wc -w" outfile
					
test4:				$(NAME)
					< file1 tr a b | tr b c > file2
					valgrind ./pipex infile "tr a b" "tr b c" outfile 
					
test5:				$(NAME)
					< file1 cat | wc -l > file2
					valgrind ./pipex infile "cat" "wc -l" outfile 
test6:				$(NAME)
					< file1 grep a | wc -l > file2
					valgrind ./pipex infile "grep a" "wc -l" outfile
					
test7:				$(NAME)
					< file1 pwd | tr o b > file2
					valgrind ./pipex infile "pwd" " tr o b" outfile

test8:				$(NAME)
					< file1 sort | uniq -c > file2
					valgrind ./pipex infile "sort" "uniq -c" outfile

test9:				$(NAME)
					< file1 sort -r | head -3 > file2
					valgrind ./pipex infile "sort -r" "head -3" outfile
					
test10:				$(NAME)
					< file1 cat | pr > file2
					valgrind ./pipex infile "cat" "pr" outfile

.PHONY:				all clean fclean re libft
