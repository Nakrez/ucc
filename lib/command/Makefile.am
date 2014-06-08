AM_CXXFLAGS = -Wall -Wextra -std=c++11
AM_CPPFLAGS = -Iinclude -I../argp
lib_LTLIBRARIES = libcommand.la
libcommand_la_SOURCES = src/basic-command.cc \
						src/callback-command.cc \
						src/boolean-command.cc \
						src/unifier-command.cc \
						src/command.cc

libcommand_la_LIBADD = ../argp/libargp.la
