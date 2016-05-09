

UTEST_SRC_PATH=$(COMPOSITE_SRC_PATH)/utest
UTEST_OBJ=$(COMPOSITE_BIN_PATH)/test.o

UTEST_OBJ_ARRAYTEST=$(COMPOSITE_BIN_PATH)/arraytest.o
UTEST_OBJ_DATATEST=$(COMPOSITE_BIN_PATH)/datest.o
UTEST_OBJ_llTEST=$(COMPOSITE_BIN_PATH)/lltest.o
UTEST_OBJ_INDEX=$(COMPOSITE_BIN_PATH)/index.o
UTEST_OBJ_EVENTS=$(COMPOSITE_BIN_PATH)/events.o
UTEST_OBJ=$(UTEST_OBJ_ARRAYTEST) $(UTEST_OBJ_DATATEST) $(UTEST_OBJ_llTEST) $(UTEST_OBJ_INDEX) $(UTEST_OBJ_EVENTS)

UTEST_BIN_ARRAYTEST=$(COMPOSITE_BIN_PATH)/composite_arraytest
UTEST_BIN_DATATEST=$(COMPOSITE_BIN_PATH)/composite_datest
UTEST_BIN_llTEST=$(COMPOSITE_BIN_PATH)/composite_lltest
UTEST_BIN_INDEX=$(COMPOSITE_BIN_PATH)/composite_index
UTEST_BIN_EVENTS=$(COMPOSITE_BIN_PATH)/composite_events
UTEST_BIN=$(UTEST_BIN_ARRAYTEST $(UTEST_BIN_DATATEST) $(UTEST_BIN_llTEST) $(UTEST_BIN_INDEX) $(UTEST_BIN_EVENTS)

#build_utest:  build_utest_events build_utest_index build_utest_array build_utest_darray build_utest_llist
build_utest:  build_utest_array build_utest_llist

run_utest: clean_utest run_utest_array run_utest_darray run_utest_index run_utest_lltest run_utest_events
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo " Unit test end with success!"
	@echo "---------------------------------------------------------------------------------"

$(COMPOSITE_BIN_PATH)/events.o: $(UTEST_SRC_PATH)/events.cpp
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Compiling $?"
	@echo "   File to compie: $@"
	@echo "   Obj file      : $?"
	$(COMPOSITE_CC) $(COMPOSITE_CFLAG) $(COMPOSITE_LOG_SETTING) -c $? -o $@
	@echo "[MAKE INFO] Compile $? succesfull!"
	@echo "---------------------------------------------------------------------------------"


build_utest_events: $(COMPOSITE_BIN_PATH)/events.o
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Linking $?"	
	$(COMPOSITE_LPP) $(COMPOSITE_LFLAG) -o $(COMPOSITE_BIN_PATH)/composite_events $(COMPOSITE_BIN_PATH)/events.o
	@echo "[MAKE INFO] Succesfull!"
	@echo "---------------------------------------------------------------------------------"
	@echo

run_utest_events: build_utest_events
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo " RUN Unit test events"
	@echo "---------------------------------------------------------------------------------"
	$(COMPOSITE_BIN_PATH)/composite_events


$(COMPOSITE_BIN_PATH)/index.o: $(UTEST_SRC_PATH)/index.cpp
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Compiling $?"
	@echo "   File to compie: $@"
	@echo "   Obj file      : $?"
	$(COMPOSITE_CC) $(COMPOSITE_CFLAG) $(COMPOSITE_LOG_SETTING) -c $? -o $@
	@echo "[MAKE INFO] Compile $? succesfull!"
	@echo "---------------------------------------------------------------------------------"


build_utest_index: $(COMPOSITE_BIN_PATH)/index.o
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Linking $?"	
	$(COMPOSITE_LPP) $(COMPOSITE_LFLAG) -o $(COMPOSITE_BIN_PATH)/composite_index $(COMPOSITE_BIN_PATH)/index.o
	@echo "[MAKE INFO] Succesfull!"
	@echo "---------------------------------------------------------------------------------"
	@echo

run_utest_index: build_utest_index
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo " RUN Unit test index"
	@echo "---------------------------------------------------------------------------------"
	$(COMPOSITE_BIN_PATH)/composite_index

$(COMPOSITE_BIN_PATH)/arraytest.o: $(UTEST_SRC_PATH)/arraytest.cpp
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Compiling $?"
	@echo "   File to compie: $@"
	@echo "   Obj file      : $?"
	$(COMPOSITE_CC) $(COMPOSITE_CFLAG) $(COMPOSITE_LOG_SETTING) -c $? -o $@
	@echo "[MAKE INFO] Compile $? succesfull!"
	@echo "---------------------------------------------------------------------------------"


build_utest_array: $(COMPOSITE_BIN_PATH)/arraytest.o
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Linking $?"	
	$(COMPOSITE_LPP) $(COMPOSITE_LFLAG) -o $(COMPOSITE_BIN_PATH)/composite_arraytest $(COMPOSITE_BIN_PATH)/arraytest.o
	@echo "[MAKE INFO] Succesfull!"
	@echo "---------------------------------------------------------------------------------"
	@echo

run_utest_array: build_utest_array
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo " RUN Unit test array"
	@echo "---------------------------------------------------------------------------------"
	$(COMPOSITE_BIN_PATH)/composite_arraytest

$(COMPOSITE_BIN_PATH)/datest.o: $(UTEST_SRC_PATH)/datest.cpp
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Compiling $?"
	@echo "   File to compie: $@"
	@echo "   Obj file      : $?"
	$(COMPOSITE_CC) $(COMPOSITE_CFLAG) $(COMPOSITE_LOG_SETTING) -c $? -o $@
	@echo "[MAKE INFO] Compile $? succesfull!"
	@echo "---------------------------------------------------------------------------------"


build_utest_darray: $(COMPOSITE_BIN_PATH)/datest.o
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Linking $?"	
	$(COMPOSITE_LPP) $(COMPOSITE_LFLAG) -o $(COMPOSITE_BIN_PATH)/composite_datest $(COMPOSITE_BIN_PATH)/datest.o
	@echo "[MAKE INFO] Succesfull!"
	@echo "---------------------------------------------------------------------------------"
	@echo

run_utest_darray: build_utest_darray
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo " RUN Unit test dynamic array"
	@echo "---------------------------------------------------------------------------------"
	$(COMPOSITE_BIN_PATH)/composite_datest

$(COMPOSITE_BIN_PATH)/lltest.o: $(UTEST_SRC_PATH)/lltest.cpp
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Compiling $?"
	@echo "   File to compie: $@"
	@echo "   Obj file      : $?"
	$(COMPOSITE_CC) $(COMPOSITE_CFLAG) $(COMPOSITE_LOG_SETTING) -c $? -o $@
	@echo "[MAKE INFO] Compile $? succesfull!"
	@echo "---------------------------------------------------------------------------------"


build_utest_llist: $(COMPOSITE_BIN_PATH)/lltest.o
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "[MAKE INFO] Linking $?"	
	$(COMPOSITE_LPP) $(COMPOSITE_LFLAG) -o $(COMPOSITE_BIN_PATH)/composite_lltest $(COMPOSITE_BIN_PATH)/lltest.o
	@echo "[MAKE INFO] Succesfull!"
	@echo "---------------------------------------------------------------------------------"
	@echo

run_utest_lltest: build_utest_llist
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo " RUN Unit test linked list"
	@echo "---------------------------------------------------------------------------------"
	$(COMPOSITE_BIN_PATH)/composite_lltest

.PHONY : clean_utest

clean_utest:
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "Clean object files: $(UTEST_OBJ)"
	-rm $(UTEST_OBJ_ARRAYTEST)
	-rm $(UTEST_OBJ_DATATEST)
	-rm $(UTEST_OBJ_llTEST)
	-rm $(UTEST_OBJ_INDEX)
	-rm $(UTEST_OBJ_EVENTS)
	@echo "Clean object files: $(UTEST_BIN)"
	-rm $(UTEST_BIN_ARRAYTEST)
	-rm $(UTEST_BIN_DATATEST)
	-rm $(UTEST_BIN_llTEST)
	-rm $(UTEST_BIN_INDEX)
	-rm $(UTEST_BIN_EVENTS)
	@echo "Object file deleted"
	@echo "---------------------------------------------------------------------------------"
	@echo

