CC = gcc
CFLAGS = -lSDL2 -lSDL2_ttf $(shell pkg-config --cflags --libs sdl2)

SRC = main.c \
      resources/colliders/snake.c \
      resources/colliders/food.c \
      resources/events/score/score.c \
      resources/colliders/sdl.c \
      resources/events/map/map.c \
      resources/events/menu/menu.c

OBJ = $(SRC:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)
