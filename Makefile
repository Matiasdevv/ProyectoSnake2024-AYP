# Variables
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lSDL2 -lSDL2_ttf
SRC = main.c resources/snake.c resources/food.c ui/score.c ui/map.c ui/draw.c ui/menu.c settings/settings.c
OBJ = $(SRC:.c=.o)
EXEC = main

# Regla principal: compilar y enlazar
all: $(EXEC)

# Compilar los archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Enlazar los objetos .o para crear el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Limpiar archivos generados
clean:
	rm -f $(OBJ) $(EXEC)

# Reglas adicionales

# Recompilar todo desde cero
rebuild: clean all

