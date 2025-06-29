# Colors
RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[0;33m
BLUE	= \033[0;34m
PURPLE	= \033[0;35m
CYAN	= \033[0;36m
WHITE	= \033[0;37m
RESET	= \033[0m

# Program name
NAME	= philo

# Directories
SRC_DIR	= src
INC_DIR	= inc
OBJ_DIR	= obj

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread #-g -fsanitize=thread
INCLUDE	= -I$(INC_DIR)

# Source files
SRCS	= $(SRC_DIR)/main.c \
		  $(SRC_DIR)/init.c \
		  $(SRC_DIR)/check_args.c \
		  $(SRC_DIR)/routine.c \
		  $(SRC_DIR)/monitor.c \
		  $(SRC_DIR)/utils.c

# Object files
OBJS	= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS	= $(INC_DIR)/philosophers.h

# Rules
all: $(NAME)

$(NAME): $(OBJS) Makefile
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ $(NAME) cleaned!$(RESET)"

re: fclean all

# Phony targets
.PHONY: all clean fclean re