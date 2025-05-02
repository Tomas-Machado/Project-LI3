# Compiler and Flags
CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0`
LDFLAGS = `pkg-config --libs glib-2.0`
INCLUDES = -Iinclude

# Pretty colors
NO_COLOR = \033[m
COMPILING_COLOR = \033[0;33m
LINKING_COLOR = \033[0;34m
DELETING_COLOR = \033[0;31m
OK_COLOR = \033[0;32m
COMPILING_STRING = "[COMPILING]"
LINKING_STRING = "[LINKING]"
DELETING_STRING = "[DELETING]"
OK_STRING = "[OK]"

# Source and object files
SRC_DIR = src
INCLUDE_DIR = include
OBJS = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

# Exclude specific object files for each target
MAIN_OBJS = $(filter-out $(SRC_DIR)/testes.o $(SRC_DIR)/interativo.o, $(OBJS))
TESTES_OBJS = $(filter-out $(SRC_DIR)/main.o $(SRC_DIR)/interativo.o, $(OBJS))
INTERATIVO_OBJS = $(filter-out $(SRC_DIR)/testes.o $(SRC_DIR)/main.o, $(OBJS))

# Build main executable
all: programa-principal programa-testes programa-interativo

programa-principal: $(MAIN_OBJS)
	@printf "%b" "$(LINKING_COLOR)$(LINKING_STRING) Building executable 'programa-principal'$(NO_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o programa-principal $(MAIN_OBJS) $(LDFLAGS)
	@printf "%b" "$(OK_COLOR)$(OK_STRING) Executable 'programa-principal' created successfully$(NO_COLOR)\n"

programa-testes: $(TESTES_OBJS)
	@printf "%b" "$(LINKING_COLOR)$(LINKING_STRING) Building executable 'programa-testes'$(NO_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o programa-testes $(TESTES_OBJS) $(LDFLAGS)
	@printf "%b" "$(OK_COLOR)$(OK_STRING) Executable 'programa-testes' created successfully$(NO_COLOR)\n"

programa-interativo: $(INTERATIVO_OBJS)
	@printf "%b" "$(LINKING_COLOR)$(LINKING_STRING) Building executable 'programa-interativo'$(NO_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o programa-interativo $(INTERATIVO_OBJS) $(LDFLAGS)
	@printf "%b" "$(OK_COLOR)$(OK_STRING) Executable 'programa-interativo' created successfully$(NO_COLOR)\n"

# Compile .c files automatically
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "%b" "$(COMPILING_COLOR)$(COMPILING_STRING) Compiling $<$(NO_COLOR)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean generated files
clean:
	@printf "%b" "$(DELETING_COLOR)$(DELETING_STRING) Removing object files, executables, and resultados files$(NO_COLOR)\n"
	@rm -f $(SRC_DIR)/*.o $(SRC_DIR)/*.d programa-principal programa-testes programa-interativo
	@rm -f resultados/*.txt resultados/*.csv
	@printf "%b" "$(OK_COLOR)$(OK_STRING) Clean completed$(NO_COLOR)\n"