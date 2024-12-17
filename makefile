# -------------------------------
# Variables Section
# -------------------------------

# Compiler and Flags
CC = arm-none-eabi-gcc
CCFLAGS = -Wall -Wextra -mcpu=cortex-m3 -mthumb

#-std=c++17 -g -O2

# Directory Structure
BUILD_DIR =00-Build
LIBDIR = 01-LIB
MCALDIR = 02-MCAL
HALDIR = 03-HAL
APPDIR = 04-APP

# Source Subdirectories
LIBSRC = $(wildcard $(LIBDIR)/*/*.c)
MCALSRC = $(wildcard $(MCALDIR)/*/*.c)
HALSRC = $(wildcard $(HALDIR)/*/*.c)
APPSRC = $(wildcard $(APPDIR)/*.c)

# Object Files (Output of Compilation in BUILD_DIR)
LIBOBJ = $(patsubst $(LIBDIR)/%.c, $(BUILD_DIR)/%.o, $(LIBSRC))
MCALOBJ = $(patsubst $(MCALDIR)/%.c, $(BUILD_DIR)/%.o, $(MCALSRC))
HALOBJ = $(patsubst $(HALDIR)/%.c, $(BUILD_DIR)/%.o, $(HALSRC))
APPOBJ = $(patsubst $(APPDIR)/%.c, $(BUILD_DIR)/%.o, $(APPSRC))

# Final Executable
TARGET = app_program.exe

# -------------------------------
# Phony Targets (Tasks)
# -------------------------------
.PHONY: all clean debug release run

# -------------------------------
# Main Build Targets
# -------------------------------

# Default Target: Build everything
all: $(LIBOBJ) $(MCALOBJ) $(HALOBJ) $(APPOBJ)


# Link all object files into the executable
#$(TARGET): $(LIBOBJ) $(MCALOBJ) $(HALOBJ) $(APPOBJ)
#	@echo "Linking all object files into $(TARGET)..."
#	@mkdir -p bin
#	$(CC) $(CCFLAGS) $(BUILD_DIR)/*.o -o $@

# -------------------------------
# Compilation Rule for .c -> .o
# -------------------------------
# Compile .c files to .o files for all directories
$(BUILD_DIR)/%.o: $(LIBDIR)/%.c
	@echo "Compiling $< into $@..."
	$(CC) $(CCFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

$(BUILD_DIR)/%.o: $(MCALDIR)/%.c
	@echo "Compiling $< into $@..."
	$(CC) $(CCFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

$(BUILD_DIR)/%.o: $(HALDIR)/%.c
	@echo "Compiling $< into $@..."
	$(CC) $(CCFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

$(BUILD_DIR)/%.o: $(APPDIR)/%.c
	@echo "Compiling $< into $@..."
	$(CC) $(CCFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

# -------------------------------
# Debug and Release Targets
# -------------------------------



# -------------------------------
# Running and Cleaning Targets
# -------------------------------

# Run the program after building
run: all
	@echo "Running the program..."
	./$(TARGET)

# Clean up all build artifacts
clean:
	@echo "Cleaning up build files..."
	@rm -rf $(BUILD_DIR)/*.o $(TARGET)
	@echo "Clean complete."
