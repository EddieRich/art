# CFLAGS is not defined by default
CXXFLAGS=-MMD -Wall -Wextra -Werror -Wno-format-overflow -std=c++17 -march=x86-64 -fdiagnostics-color=always

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
DEP=$(OBJ:%.o=%.d)

EXE=art

# add any additional libraries here ...
# $(addprefix -l, m pthread GL)
LIBS=$(addprefix -l,)

.PHONY: clean

debug: CXXFLAGS += -g -Wno-unused-parameter -Wno-unused-variable
debug: $(EXE)

remake: clean debug
.NOTPARALLEL: remake

test: debug
	./art > test.ppm
	open test.ppm
.NOTPARALLEL: test

release: CXXFLAGS += -Os -s -Wno-unused-result -fno-ident -fno-asynchronous-unwind-tables -faggressive-loop-optimizations
release: clean $(EXE)
.NOTPARALLEL: release

clean:
	$(RM) $(OBJ) $(DEP) $(EXE) test.ppm

install: release
	sudo cp $(EXE) /usr/local/bin/$(EXE)

$(EXE): $(OBJ)
	g++ -o $@ $^ $(LIBS)

-include $(DEP)
