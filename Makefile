BUILD=./build/
MAIN=kangaroo
TEST_MAIN=kangaroo_tests

WIDTH  = 200
HEIGHT = 200

.PHONY: tests
tests: $(BUILD)/$(TEST_MAIN)
	$(BUILD)/$(TEST_MAIN)

.PHONY: run
run: $(BUILD)/$(MAIN)
	$(BUILD)/$(MAIN) $(WIDTH) $(HEIGHT)

$(BUILD)/$(MAIN): $(BUILD) $(BUILD)/CMakeCache.txt CMakeLists.txt
	make -sC $(BUILD)

$(BUILD)/$(TEST_MAIN): $(BUILD) $(BUILD)/CMakeCache.txt CMakeLists.txt
	make -sC $(BUILD)

$(BUILD)/CMakeCache.txt: CMakeLists.txt
	cd $(BUILD); cmake ..

$(BUILD):
	mkdir $(BUILD)

.PHONY: clean
clean:
	rm -rf build/
