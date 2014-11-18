#!/bin/make
SHELL=/bin/bash

#Define the virtual paths
vpath %.cpp src/
vpath %.hpp inc/
vpath %.o obj/

#Set some of the compile options
CXX = g++
CINCLUDEDIRS = -Iinc
CXXFLAGS = -fPIC -g -std=c++11 -Wall $(CINCLUDEDIRS)
LDLIBS = -ldl -lpthread
c++SrcSuf = cpp

#Set the name of the program to be compiled
PROGRAM = texttoroot

#Define Objects
MAINO = main.o
TOKENIZERO = Tokenizer.o

#Make the object list and prefix the object directory
OBJS = $(MAINO) $(TOKENIZERO)
OBJDIR = obj
OBJS_W_DIR = $(addprefix $(OBJDIR)/,$(OBJS))

#Add the ROOT config stuff to the compilation
ROOTCONFIG   := root-config
CXXFLAGS     += $(shell $(ROOTCONFIG) --cflags)
LDFLAGS      += $(shell $(ROOTCONFIG) --ldflags)
LDLIBS       += $(shell $(ROOTCONFIG) --libs)

.SUFFIXES: .$(c++SrcSuf)

all: $(OBJS_W_DIR) $(PROGRAM)

$(OBJS_W_DIR): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(PROGRAM): $(OBJS_W_DIR)
	$(CXX) $(CXXFLAGS) $(LDLIBS) $^ -o $@

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean so doc
clean:
	@echo "Cleaning..."
	@rm -f $(OBJDIR)/*.o $(PROGRAM) *~ src/*~ include/*~

so: $(HEADER_NAME)
	g++ -shared $(OBJDIR)/$(PIPESO)  -o $(SO_NAME_FULL)
	cp $(SO_NAME_FULL) $(SO_INSTALL_PATH)
	ln -sf $(SO_INSTALL_PATH)/$(SO_NAME_W_VERSION) $(SO_INSTALL_PATH)/$(SO_NAME)
	cp $^ $(HEADER_INSTALL_PATH)

doc: doc/doxyfile
	@doxygen $^
