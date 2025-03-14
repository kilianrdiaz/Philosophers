NAME = philo

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -I$(INC_DIR)

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/check_args.c $(SRC_DIR)/init.c \
	$(SRC_DIR)/routine.c

# Regla principal
all: $(NAME)

# Compilar el ejecutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilar archivos .c en .o y asegurar que el directorio obj existe
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear el directorio de objetos si no existe
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpiar archivos intermedios
clean:
	rm -rf $(OBJ_DIR)

# Limpiar todo (objetos y ejecutable)
fclean: clean
	rm -f $(NAME)

# Volver a compilar desde cero
re: fclean all

# No tratar estos nombres como archivos
.PHONY: all clean fclean re
