# Using µnit-plus is very simple; just include the header and add the C++
# file to your sources.  That said, here is a simple Makefile to build
# the example.

CXXSTD:=11
OPENMP:=n
ASAN:=n
UBSAN:=n
EXTENSION:=
TEST_ENV:=
CXXFLAGS:=
AGGRESSIVE_WARNINGS=n

using_pgcc:=n
ifeq ($(CXX),pgCC)
        using_pgcc:=y
endif

ifeq ($(CXX),pgc++)
        using_pgcc:=y
endif

ifeq ($(using_pgcc),y)
        #FIXME untested
        CXXFLAGS+=--c++$(CXXSTD)
else
        CXXFLAGS+=-std=c++$(CXXSTD)
endif

ifeq ($(OPENMP),y)
        ifeq ($(using_pgcc),y)
                CXXFLAGS+=-mp
        else
                CXXFLAGS+=-fopenmp
        endif
endif

ifneq ($(SANITIZER),)
        CXXFLAGS+=-fsanitize=$(SANITIZER)
endif

ifneq ($(using_pgcc),y)
        ifeq ($(EXTRA_WARNINGS),y)
                CXXFLAGS+=-Wall -Wextra -Werror
        endif

        ifeq ($(ASAN),y)
                CXXFLAGS+=-fsanitize=address
        endif

        ifeq ($(UBSAN),y)
                CXXFLAGS+=-fsanitize=undefined
        endif
endif

example$(EXTENSION): munit.hpp munit.cpp example.cpp
	$(CXX) $(CXXFLAGS) -o $@ munit.cpp example.cpp

test:
	$(TEST_ENV) ./example$(EXTENSION)

clean:
	rm -f example$(EXTENSION)

all: example$(EXTENSION)
