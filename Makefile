CC = gcc
CFLAGS = -Wall -Wextra -g

OUT_DIR = out

TARGET = $(OUT_DIR)/simple-sql

SRCS = main.c
OBJS = $(patsubst %.c, $(OUT_DIR)/%.o, $(SRCS))

all: $(OUT_DIR) $(TARGET)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

$(OUT_DIR)/%.o: %.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OUT_DIR)

.PHONY: all clean

