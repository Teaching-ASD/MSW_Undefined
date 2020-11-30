FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
	libgtest-dev \
	cmake \
	make \
	valgrind \
	cppcheck \
	g++ g++-10 \
	libpthread-stubs0-dev
RUN cd /usr/src/gtest
RUN cmake CMakeLists.txt
RUN make .
RUN ln -st /usr/lib/ /usr/src/gtest/libgtest.a
RUN ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a
RUN apt-get install -y git
RUN rm -rf /var/lib/apt/lists/*
