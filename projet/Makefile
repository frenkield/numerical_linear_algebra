INCLDIR := include
BINDIR := bin
CC := g++
CFLAGS := -std=c++11 -Wall -Wno-sign-compare -I $(INCLDIR)

# ===========================================

all:
	@echo Saisissez \"make clean\", \"make test\" ou \"make visualisation\".

OBJDIR := obj
SRCDIR := src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/, $(subst .cpp,.o, $(SRCS)))

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLDIR)/%.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINDIR) :
	mkdir -p $(BINDIR)

.PHONY: clean
clean :
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

silent:
	@:

# ===========================================

VISUALISATION_EXE := bin/visualisation
VISUALISATION_OBJDIR := obj/visualisation
VISUALISATION_SRCDIR := src/visualisation
VISUALISATION_SRCS := $(wildcard $(VISUALISATION_SRCDIR)/*.cpp)
VISUALISATION_OBJS := $(subst $(VISUALISATION_SRCDIR)/,$(VISUALISATION_OBJDIR)/, $(subst .cpp,.o, $(VISUALISATION_SRCS)))

.PHONY: visualisation
visualisation : $(VISUALISATION_EXE) | silent

$(VISUALISATION_EXE) : $(BINDIR) $(VISUALISATION_OBJDIR) $(VISUALISATION_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/visualisation $(VISUALISATION_OBJS) $(OBJS)

$(VISUALISATION_OBJDIR) :
	mkdir -p $(VISUALISATION_OBJDIR)

$(VISUALISATION_OBJDIR)/%.o : $(VISUALISATION_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# ===========================================

TEST_EXE := bin/test
TEST_OBJDIR := obj/test
TEST_SRCDIR := test
TEST_SRCS := $(wildcard $(TEST_SRCDIR)/*.cpp)
TEST_OBJS := $(subst $(TEST_SRCDIR)/,$(TEST_OBJDIR)/, $(subst .cpp,.o, $(TEST_SRCS)))

.PHONY: test
test : $(TEST_EXE) | silent

$(TEST_EXE) : $(BINDIR) $(TEST_OBJDIR) $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/test $(TEST_OBJS) $(OBJS)

$(TEST_OBJDIR) :
	mkdir -p $(TEST_OBJDIR)

$(TEST_OBJDIR)/%.o : $(TEST_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

