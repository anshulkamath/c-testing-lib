CXX = cc
CXXFLAGS = -g -pedantic -Wall -Wextra -std=c17

testing-test: testing.o testing-test.o
	${CXX} ${CXXFLAGS} -o $@ $^

testing.o: testing.c testing.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

testing-test.o: testing-test.c testing.h
	${CXX} ${CXXFLAGS} -c -o $@ $<

libtest.a: testing.o
	ar rcs $@ $<

clean:
	rm -rf *.o *.dSYM testing-test *.a