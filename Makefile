INC := ./raylib-5.5_linux_amd64/include
LIBS := ./raylib-5.5_linux_amd64/lib

CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -ggdb -Os $(addprefix -I, $(INC))
LDFLAGS := -l:libraylib.a -lm $(addprefix -L, $(LIBS))

EXE := renderer

SRCS := $(wildcard ./*.c)
OBJS := $(SRCS:%.c=%.o)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean all debug

debug: CFLAGS += -DDEBUG
debug: $(EXE)

clean:
	$(RM) -v ./*.o $(EXE)
