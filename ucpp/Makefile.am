AM_CPPFLAGS = -Iinclude -I../lib/command/include
bin_PROGRAMS = ucpp
ucpp_SOURCES = src/main.cc \
			   src/ucpp.cc \
			   src/macro.cc \
			   src/token.cc \
			   src/lexer-state.cc \
			   src/ucpp-lexer.cc \
			   src/ucpp-process.cc
ucpp_LDADD   = ../lib/command/libcommand.la
