
GROUND_SRC_PATH=$(COMPOSITE_SRC_PATH)/ground
GROUND_OBJ=$(COMPOSITE_BIN_PATH)/appmain.o

.PHONY : clean_ground_obj print_banner

#$(COMPOSITE_BIN_PATH)/mdchain.o: $(GROUND_SRC_PATH)/mdchain.cpp
#	@echo
#	@echo "[MAKE INFO] Compiling $?"
#	@echo "   File to compie: $?"
#	@echo "   Obj file      : $@"
#	$(COMPOSITE_CC) $(COMPOSITE_CFLAG) $(COMPOSITE_LOG_SETTING) -c $? -o $@
#	@echo "[MAKE INFO] Compile $? succesfull!"
#	@echo


$(COMPOSITE_BIN_PATH)/appmain.o: $(GROUND_SRC_PATH)/appmain.cpp 
	@echo
	@echo "[MAKE INFO] Compiling $?"
	@echo "   File to compie: $?"
	@echo "   Obj file      : $@"
	$(COMPOSITE_CC) $(COMPOSITE_CFLAG) $(COMPOSITE_LOG_SETTING) -c $? -o $@
	@echo "[MAKE INFO] Compile $? succesfull!"
	@echo

compile_ground: $(GROUND_OBJ)

clean_ground_obj:
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "Clean object files: $(COMPOSITE_BIN_PATH)/appmain.o"
	-rm $(COMPOSITE_BIN_PATH)/appmain.o
	@echo "Object file deleted"
	@echo "---------------------------------------------------------------------------------"
	@echo
	