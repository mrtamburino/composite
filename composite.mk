PROJECT_HOME=/home/ale/workspace/Projects/composite

include $(PROJECT_HOME)/base.mk
include $(PROJECT_HOME)/ground.mk
include $(PROJECT_HOME)/utest.mk

.PHONY : clean_composite_obj
 
 clean_composite_obj:
	@echo
	@echo "---------------------------------------------------------------------------------"
	@echo "Clean object files: $(COMPOSITE_BIN_PATH)/*"
	-rm $(COMPOSITE_BIN_PATH)/*
	@echo "Object file deleted"
	@echo "---------------------------------------------------------------------------------"
	@echo
