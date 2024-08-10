TARGET_EXEC := combat_sim

BUILD_DIR := ./build
SRC_DIR := ./src
TEST_DIR := ./tests

SRCS := $(SRC_DIR)/combat_sim.c $(SRC_DIR)/character.c $(SRC_DIR)/combat.c $(SRC_DIR)/map.c $(SRC_DIR)/utils.c
ROLL_SRCS := $(SRC_DIR)/rolltest.c $(SRC_DIR)/utils.c
MAP_SRCS := $(SRC_DIR)/maptest.c $(SRC_DIR)/map.c

CFLAGS := $(CFLAGS) -Wall
DEBUG_FLAGS := -O0 -g

RELEASE := $(BUILD_DIR)/$(TARGET_EXEC)
DEBUG := $(BUILD_DIR)/$(TARGET_EXEC)

all: release

test: rolltest maptest

release: $(SRCS)
	mkdir -p $(dir $(RELEASE))
	$(CC) $(CFLAGS) $? -o $(RELEASE)

rolltest: $(ROLL_SRCS)
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $? -o $(TEST_DIR)/rolltest

maptest: $(MAP_SRCS)
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) $? -o $(TEST_DIR)/maptest

debug: $(SRCS)
	mkdir -p $(dir $(DEBUG))
	$(CC) $(DEBUG_FLAGS) $? -o $(DEBUG)

clean:
	rm -r $(BUILD_DIR)
