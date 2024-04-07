CC := g++
CFLAGS := -Wall -Wextra -Werror -D DEVENV

MODULE = button

INCLUDE_DIR := include
LIB_DIR := lib
TEST_DIR := test
TEST_EXE := test
BUILD_DIR := build
UNITY_DIR := $(TEST_DIR)/unity
TEST_MODULE := $(TEST_DIR)_$(MODULE)

INCLUDES := $(LIB_DIR)/$(MODULE) $(TEST_DIR)/$(TEST_MODULE) $(UNITY_DIR) $(INCLUDE_DIR)
INCLUDES := $(addprefix -I./, $(INCLUDES))

OBJECTS := $(notdir $(wildcard $(LIB_DIR)/$(MODULE)/*.cpp) $(wildcard $(TEST_DIR)/*/*.cpp))
OBJECTS := $(addprefix $(BUILD_DIR)/, $(OBJECTS:.cpp=.o))

all: .mkbuild $(TEST_EXE)
	@echo "=========== The Targets ==========="
	@echo "=> clean: to clean"
	@echo "=> check: to run the test"
	@echo "==================================="

$(BUILD_DIR)/$(TEST_EXE): $(OBJECTS)
	@$(CC) --coverage $^ -o $@

$(BUILD_DIR)/%.o: $(LIB_DIR)/$(MODULE)/%.cpp
	@$(CC) -MMD $(CFLAGS) --coverage -o $@ $(INCLUDES) -c $<

$(BUILD_DIR)/%.o : $(TEST_DIR)/*/%.cpp
	@$(CC) -MMD $(CFLAGS) -o $@ $(INCLUDES) -c $<

check: .mkbuild $(BUILD_DIR)/$(TEST_EXE)
	@echo "======================================"
	@echo "============ Run The Test ============"
	@echo "======================================"
	@echo ""
	@./$(BUILD_DIR)/$(TEST_EXE); \
	gcovr -r . --html-details -o $(BUILD_DIR)/index.html

# Include the automatically generated dependencies
-include $(OBJECTS:.o=.d)

.PHONY: clean .mkbuild check all

clean:
	@rm -rf $(BUILD_DIR)

.mkbuild:
	@mkdir -p $(BUILD_DIR)
