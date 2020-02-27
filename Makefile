include environment.mk

TARGET_GAME     := $(BUILD_DIR)/hogl
COPY_ENGINE_LIB := $(LIB_DIR)/$(ENGINE_LIB)

.PHONY:      \
all          \
engine       \
clean-hogl   \
clean-engine \
clean        \
resources    \

all: $(TARGET_GAME)

$(TARGET_GAME): $(OBJS) $(COPY_ENGINE_LIB) resources | $(BUILD_DIR)
	$(CXX) $(OBJS) $(LD_ENGINE_FLAGS) $(LD_FLAGS) -o $@

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(COPY_ENGINE_LIB): engine | $(LIB_DIR)
	cp $(ENGINE_DIR)/$(BUILD_DIR)/$(ENGINE_LIB) $(@D)

$(BUILD_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

engine:
	$(MAKE) -C $(ENGINE_DIR)

resources: | $(BUILD_DIR)
	ln -sfT ../$(RES_DIR) $(BUILD_DIR)/$(RES_DIR)

clean-hogl:
	$(RM) -r $(OBJ_DIR) $(BUILD_DIR) $(LIB_DIR)

clean-engine:
	$(MAKE) -C $(ENGINE_DIR) clean

clean: clean-hogl clean-engine
