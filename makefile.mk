CC = gcc
CFLAGS = -Wall -Wextra

# Define the target executable
TARGET = a.out

# Define the source files
SRCS = src/interfaces/admin.c src/interfaces/faculty.c src/utilityServices/generateBatchId.c src/utilityServices/date.c src/utilityServices/inputValidation.c src/services/adminService.c src/services/facultyService.c src/main.c 

# Build rule for the target executable
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Clean rule to remove generated files
clean:
	rm -f $(TARGET)