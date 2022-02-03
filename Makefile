# COLORS
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

# SYMBOLS
INFO = $(BLUE)ℹ️  $(NOC)
SUCCESS = $(GREEN)✅  $(GREEN)
WARNING = $(YELLOW)⚠️  $(YELLOW)
ERROR = $(RED)❌$(WHITE)  $(RED)

# Binary
NAME=minishell

# Path
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INCDIR = ./includes

# Leaks cmd
LEAKS_CMD = valgrind --leak-check=yes

# Name
SRC_NAME =	main.c \
			app.c \
			engine.c \
			system/lexer.c \
			system/parser.c \
			system/expander.c \
			system/executor.c \
			builtins/dispatcher.c \
			builtins/echo.c \
			builtins/exit.c \
			builtins/env.c \
			builtins/cd.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c \
			misc/ctrl_handler.c \
			misc/delimiter.c \
			misc/native_cmds.c \
			utils/native_cmds.c \
			utils/files.c \
			utils/init_commands.c \
			utils/pipe.c \
			utils/tokens.c \
			utils/commands.c \
			utils/outputs.c \
			utils/env.c \
			utils/map.c \
			utils/paths.c \
			utils/app.c \
			utils/parser.c \
			utils/arrays.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

# Files
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# Libft
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft -lreadline

# Flags
CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -Werror

all: obj $(FT_LIB) $(NAME)

obj:
	@echo "$(INFO)Creating objects folder... $(NOC)"
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/builtins
	@mkdir -p $(OBJ_PATH)/system
	@mkdir -p $(OBJ_PATH)/misc
	@mkdir -p $(OBJ_PATH)/commands
	@mkdir -p $(OBJ_PATH)/handlers
	@mkdir -p $(OBJ_PATH)/utils
	@echo "$(SUCCESS)Objects folder created successfully$(NOC)"

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@echo "$(INFO)Building libft library...$(NOC)"
	@make -C $(FT)
	@echo "$(SUCCESS)Libft library built successfully!$(NOC)"

$(NAME): $(OBJ)
	@echo "$(INFO)Building $(NAME)...$(NOC)"
	@$(CC) $(OBJ) $(FT_LNK) -o $@
	@echo "$(SUCCESS)$(NAME) built successfully!$(NOC)"

clean:
	@echo "$(INFO)Deleting .o files...$(NOC)"
	@rm -rf $(OBJ_PATH)
	@echo "$(SUCCESS).o files deleted successfully!$(NOC)"
	@echo "$(INFO)Deleting libft files..."
	@make -C $(FT) clean
	@echo "$(SUCCESS)Libft files deleted successfully!$(NOC)"

fclean: clean
	@echo "$(INFO)Deleting $(NAME)...$(NOC)"
	@rm -rf $(NAME)
	@echo "$(SUCCESS)$(NAME) deleted successfully!$(NOC)"
	@make -C $(FT) fclean

leaks: $(NAME)
	$(LEAKS_CMD) ./$(NAME)

run: $(NAME)
	@./$(NAME)

re: fclean all

.PHONY:			all clean fclean re leaks run