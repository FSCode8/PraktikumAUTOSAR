CC = gcc
CFLAGS = -Wall -std=c99
# -Wextra

# Source files
SRCS = autosar_simu.c simulatedControllFlow.c runnable_Input_Controller.c runnable_Cornering_Light_Logic.c

# Object files
OBJS = $(SRCS:.c=.o)

# Output program
TARGET = program

# Build target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
#	rm -f $(OBJS)	# delete object files after linking

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f *.o $(TARGET)
