
# slstatus version
VERSION = 0.1

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# flags
CPPFLAGS = -I$(X11INC) -D_DEFAULT_SOURCE
CFLAGS   = -std=c99 -pedantic -Wall -Wextra -Os
LDFLAGS  = -L$(X11LIB) -s
LDLIBS   = -lX11

# compiler and linker
CC = cc

BUILD = build
FILES = util components/datetime components/ram components/cpu components/keymap components/sound slstatus
SRC = $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(FILES)))
REQ = src/config.h src/arg.h src/slstatus.h

all: slstatus


$(BUILD)/%.o: src/%.c $(REQ) | $(BUILD)/components
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

$(BUILD)/components:
	mkdir -p $(BUILD)/components


slstatus: $(OBJ)
	$(CC) -o $@ $(LDFLAGS) $(OBJ) $(LDLIBS)

clean:
	rm -rf $(BUILD) slstatus

install: all
	mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	cp -f slstatus "$(DESTDIR)$(PREFIX)/bin"
	chmod 755 "$(DESTDIR)$(PREFIX)/bin/slstatus"
	mkdir -p "$(DESTDIR)$(MANPREFIX)/man1"
	cp -f slstatus.1 "$(DESTDIR)$(MANPREFIX)/man1"
	chmod 644 "$(DESTDIR)$(MANPREFIX)/man1/slstatus.1"

	rm -rf $(BUILD) slstatus

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/slstatus"
	rm -f "$(DESTDIR)$(MANPREFIX)/man1/slstatus.1"

.PHONY: clean install uninstall
