.PHONY: clean run test

all: dirs main ut_main

SRC = src/Device/Device.h \
		src/Device/gateAnd.h \
		src/Device/gateNot.h \
		src/Device/gateOR.h \
		src/Device/iPin.h \
		src/Device/oPin.h \
		src/LogicSimulator.h

OBJ = obj/LogicSimulator.o

TEST = test/Device/ut_gateAnd.h \
		test/Device/ut_gateNot.h \
		test/Device/ut_gateOR.h \
		test/Device/ut_iPin.h \
		test/Device/ut_oPin.h \
		test/ut_LogicSimulator.h 

main: src/main.cpp src/TextUI.h $(SRC) $(OBJ)
	g++ -std=c++17 src/main.cpp $(OBJ) -o bin/main -lpthread

ut_main: test/ut_main.cpp $(TEST) $(SRC) $(OBJ)
	g++ -std=c++17 test/ut_main.cpp $(OBJ) -o bin/ut_main -lgtest -lpthread

obj/LogicSimulator.o: src/LogicSimulator.h src/LogicSimulator.cpp
	g++ -std=c++17 -c src/LogicSimulator.cpp -o obj/LogicSimulator.o

dirs:
	mkdir -p bin
	mkdir -p obj
clean:
	rm -rf bin obj

run: all
	bin/main

test: all
	bin/ut_main

exec: test
	bin/main

valgrind: clean all
	valgrind \
	--tool=memcheck --error-exitcode=1 --track-origins=yes --leak-check=full --leak-resolution=high \
	--num-callers=50 --show-leak-kinds=definite,possible --show-error-list=yes \
	bin/ut_main --gtest_output=xml:result.xml




