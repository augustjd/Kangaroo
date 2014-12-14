BUILD=./build
MAIN=kangaroo
TEST_MAIN=kangaroo_tests
SCENE=./cbox.xml

.PHONY: tests
tests: $(BUILD)/$(TEST_MAIN)
	$(BUILD)/$(TEST_MAIN)

.PHONY: run
run: $(BUILD)/$(MAIN)
	$(BUILD)/$(MAIN) $(SCENE)

$(BUILD)/$(MAIN): $(BUILD) $(BUILD)/CMakeCache.txt CMakeLists.txt
	make -sC $(BUILD)

$(BUILD)/$(TEST_MAIN): $(BUILD) $(BUILD)/CMakeCache.txt CMakeLists.txt
	make -sC $(BUILD)

$(BUILD)/CMakeCache.txt: CMakeLists.txt
	cd $(BUILD); cmake ..

remake: $(BUILD)/$(MAIN) $(BUILD)/$(TEST_MAIN)

$(BUILD):
	mkdir $(BUILD)

.PHONY: clean
clean:
	rm -rf build/
