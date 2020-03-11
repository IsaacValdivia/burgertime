#
# Set compiler.
#
CC=g++

#
# Set flags.
#

# Optional flags.

CFLAGS=-Wall -Wextra

# Required flags.

CFLAGS+=-MD -MP # Autogenerate dependencies.
CFLAGS+=-ggdb -std=c++11
CFLAGS+=-Iinclude

# Required libraries

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

#
# Directories.
#
BINDIR=bin
OBJDIR=obj
SRCDIR=src

#
# Transforms file basenames into $1 files with object suffix in the OBJDIR
# directory.
# Exp: one two -> $(OBJDIR)/one.o $(OBJDIR)/two.o
#
define name_to_object
	$(addsuffix .o,$(addprefix $(OBJDIR)/,$(1)))
endef

#
# Files.
#
SRCS:=$(wildcard $(SRCDIR)/*.cpp)
OBJS:=$(subst $(SRCDIR),$(OBJDIR),$(SRCS:%.cpp=%.o))
DEPS:=$(subst $(SRCDIR),$(OBJDIR),$(SRCS:%.cpp=%.d))

#
# Executables.
#
CHEF=$(BINDIR)/chef
_CHEF_OBJS=main BurgerTimeController InputSystem BurgerTimeStateMachine MainScreenStateMachine BT_sprites HighScores
CHEF_OBJS=$(call name_to_object,$(_CHEF_OBJS))

MAIN_LORIEN=$(BINDIR)/main_lorien
_MAIN_LORIEN_OBJS=main_lorien BT_sprites
MAIN_LORIEN_OBJS=$(call name_to_object,$(_MAIN_LORIEN_OBJS))

#
# Generate executables
#
$(CHEF): $(CHEF_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(MAIN_LORIEN): $(MAIN_LORIEN_OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

#
# Generate objects.
#
$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

#
# Dependencies to force the creation of $(BINDIR) and $(OBJDIR) directories.
#
$(BINDIR):
	@mkdir -p $@
$(OBJDIR):
	@mkdir -p $@

#
# Include dependencies.
#
-include $(DEPS)

#
# Rules
#
.DEFAULT_GOAL:=all
.PHONY: all
all: $(CHEF) $(MAIN_LORIEN)

chef: $(CHEF)

main_lorien: $(MAIN_LORIEN)

.PHONY: clean
clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*