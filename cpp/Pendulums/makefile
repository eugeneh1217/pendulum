GTEST_DIR = googletest/googletest
GTEST_DEST = build\test

clean: build\test
	if exist build ( rmdir /S/Q build )
	if exist googletest (rmdir /S/Q googletest)

make create-build:
	if not exist build ( mkdir build\test )

get-gtest:
	git clone https://github.com/google/googletest.git -b release-1.11.0

compile-gtest:
	g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
		-c ${GTEST_DIR}/src/gtest-all.cc -o ${GTEST_DEST}/gtest-all.o

archive-gtest: $(GTEST_DEST)/gtest-all.o
	ar -rv $(GTEST_DEST)/libgtest.a $(GTEST_DEST)/gtest-all.o

delete-gtest.o: ${GTEST_DEST}\gtest-all.o
	del ${GTEST_DEST}\gtest-all.o

build-gtest:
	make create-build
	@if not exist googletest ( \
		make get-gtest \
	)
	@if not exist $(GTEST_DEST)/libgtest.a ( \
		make compile-gtest && \
		make archive-gtest && \
		make delete-gtest.o \
	)

build-tests: build-gtest
	g++ -isystem ${GTEST_DIR}/include test/*.cpp $(GTEST_DEST)/libgtest.a -o build/test/test

run-tests: build-tests
	build\test\test.exe
