CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -lwinmm

SRC = src/main.c                    \
      src/Board.c                   \
      src/Piece.c                   \
      src/Input.c                   \
      src/Tetromino.c               \
      src/Game.c                    \
      src/renderer/Renderer.c       \
      src/renderer/GameRenderer.c   \
      src/renderer/MenuRenderer.c   \
      src/renderer/LeaderboardRenderer.c

TARGET = tetris.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	del /Q $(TARGET) 2>nul || rm -f $(TARGET)