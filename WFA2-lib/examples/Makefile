###############################################################################
# Definitions
###############################################################################
FOLDER_WFA=..
FOLDER_LIB=../lib
FOLDER_BIN=bin

###############################################################################
# Rules
###############################################################################
LIB_WFA=$(FOLDER_LIB)/libwfa.a
LIBS=-fopenmp -lm -fdump-rtl-expand -g
ifeq ($(UNAME), Linux)
  LIBS+=-lrt 
endif
CC:=gcc
CPP:=g++
all: setup examples_c examples_cpp
	
examples_c: *.c $(LIB_WFA)
	$(CC) $(CC_FLAGS) -L$(FOLDER_LIB) -I$(FOLDER_WFA) wfa_basic.c -o $(FOLDER_BIN)/wfa_basic -lwfa $(LIBS)
	$(CC) $(CC_FLAGS) -L$(FOLDER_LIB) -I$(FOLDER_WFA) wfa_adapt.c -o $(FOLDER_BIN)/wfa_adapt -lwfa $(LIBS)
	$(CC) $(CC_FLAGS) -L$(FOLDER_LIB) -I$(FOLDER_WFA) wfa_repeated.c -o $(FOLDER_BIN)/wfa_repeated -lwfa $(LIBS)
	$(CC) $(CC_FLAGS) -L$(FOLDER_LIB) -I$(FOLDER_WFA) showcase.c -o $(FOLDER_BIN)/show -lwfa $(LIBS)
examples_cpp: *.cpp $(LIB_WFA)
	$(CPP) $(CC_FLAGS) -L$(FOLDER_LIB) -I$(FOLDER_WFA) wfa_bindings.cpp -o $(FOLDER_BIN)/wfa_bindings -lwfacpp $(LIBS)
	$(CPP) $(CC_FLAGS) -L$(FOLDER_LIB) -I$(FOLDER_WFA) wfa_lambda.cpp -o $(FOLDER_BIN)/wfa_lambda -lwfacpp $(LIBS)
	
setup:
	@mkdir -p $(FOLDER_BIN)

clean: 
	rm -rf $(FOLDER_BIN)
