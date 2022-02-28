INCLDIR := include
OBJDIR := obj
SRCDIR := src
BINDIR := bin
CC := g++
CFLAGS := -std=c++11 -Wall -I $(INCLDIR)

# ===========================================

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(subst $(SRCDIR)/,$(OBJDIR)/, $(subst .cpp,.o, $(SRCS)))

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLDIR)/%.hpp
	$(CC) $(CFLAGS) -c -o $@ $<

# ===========================================

.PHONY: exercices
exercices : makedir src/exercices/exercices_main

EXERCICES_OBJDIR := obj/exercices
EXERCICES_SRCDIR := src/exercices

EXERCICES_SRCS = $(wildcard $(EXERCICES_SRCDIR)/*.cpp)
EXERCICES_SRCS := $(filter-out src/exercices/exercices_main.cpp, $(EXERCICES_SRCS))

EXERCICES_OBJS = $(subst $(EXERCICES_SRCDIR)/,$(EXERCICES_OBJDIR)/, $(subst .cpp,.o, $(EXERCICES_SRCS)))

src/exercices/exercices_main : %: %.cpp $(EXERCICES_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/exercices $^

$(EXERCICES_OBJDIR)/%.o : $(EXERCICES_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# ===========================================

.PHONY: test
test : makedir test/test_main

TEST_OBJDIR := obj/test
TEST_SRCDIR := test

TEST_SRCS = $(wildcard $(TEST_SRCDIR)/*.cpp)
TEST_SRCS := $(filter-out test/test_main.cpp, $(TEST_SRCS))

TEST_OBJS = $(subst $(TEST_SRCDIR)/,$(TEST_OBJDIR)/, $(subst .cpp,.o, $(TEST_SRCS)))

test/test_main : %: %.cpp $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/test $^

$(TEST_OBJDIR)/%.o : $(TEST_SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# ===========================================

.PHONY: clean
clean :
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

.PHONY: makedir
makedir :
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(TEST_OBJDIR)
	mkdir -p $(EXERCICES_OBJDIR)

.PHONY: print
print :
	echo $(SRCS)
	echo $(OBJS)

#Remarks:
# $@ : filename representing the target
# $< : filename of the first prerequisite
# $^ : filenames of all prerequisites, separated by spaces. Dupplicated are removed.
# $? : names of all prerequisites that are newer than the target, separated by spaces
# $+ : similar to $^ but include dupplicates
# $* : stem of target file (filename without suffix)
