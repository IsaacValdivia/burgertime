# Set the compiler.
CC=g++-8

CFLAGS+=-MD -MP # Autogenerate dependencies.
CFLAGS+=-O0 -ggdb -std=c++17
CFLAGS+=-Iinclude

LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs

# Directories.
BINDIR=bin
OBJDIR=obj
SRCDIR=src

# Src files and object files.
SRCS:=$(wildcard $(SRCDIR)/*.cpp)
OBJS:=$(subst $(SRCDIR),$(OBJDIR),$(SRCS:%.cpp=%.o))

.PHONY: all
all: $(BINDIR)/main

main: $(BINDIR)/main

# Dependencies to force the creation of the $(BINDIR) directory
# @: suppress the echoing of the command
$(BINDIR):
	@mkdir -p $@
$(OBJDIR):
	@mkdir -p $@

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create list of auto dependencies
AUTODEPS:=$(subst $(SRCDIR),$(OBJDIR),$(SRCS:%.cpp=%.d))
# https://www.gnu.org/software/make/manual/html_node/Include.html#Include
-include $(AUTODEPS)

$(BINDIR)/main: $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean
clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*