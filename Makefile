# Compiler and common flags
CC = gcc
# Added -Wextra for more warnings and -g for debugging symbols, which is great for tests
CFLAGS = -Wall -Wextra -std=c99 -g

# --- File Definitions ---

# The target name for your main application
APP_TARGET = program

# The target name for your test executable
TEST_TARGET = run_tests

# Source files for your main application's entry point
APP_MAIN_SRC = main_program.c

# Source files for your library/modules (shared between app and tests)
# Note the use of backslashes for readability
LIB_SRCS = simulatedControllFlow.c \
		   autosar_simu.c \
           runnable_Input_Controller.c \
           runnable_Indicator_Logic.c \
           runnable_Cornering_Light_Logic.c \
           runnable_Message_Controller.c \
           runnable_LM.c

# Source files for the testing framework
TEST_FRAMEWORK_SRCS = my_test.c

# Source file for the test runner (contains main() for tests)
TEST_RUNNER_SRC = test_runner.c

# --- Object File Generation ---

# Automatically generate object file names from source files
APP_MAIN_OBJ = $(APP_MAIN_SRC:.c=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)
TEST_FRAMEWORK_OBJS = $(TEST_FRAMEWORK_SRCS:.c=.o)
TEST_RUNNER_OBJ = $(TEST_RUNNER_SRC:.c=.o)

# --- Build Rules ---

# The default target when you just run "make"
all: $(APP_TARGET)

# Rule to build the main application executable
# It depends on the main entry object and the shared library objects
$(APP_TARGET): $(APP_MAIN_OBJ) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to build the test runner executable
# It depends on the test runner object, the test framework, and the shared library objects
$(TEST_TARGET): $(TEST_RUNNER_OBJ) $(TEST_FRAMEWORK_OBJS) $(LIB_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# A new convenient target to build AND run the tests in one command
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Generic rule to compile any .c file into a .o file
# This is used by all targets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove all generated files
clean:
	rm -f $(APP_TARGET) $(TEST_TARGET) *.o

clean_objs:
	rm -f *.o

# Phony targets are not files
.PHONY: all test clean