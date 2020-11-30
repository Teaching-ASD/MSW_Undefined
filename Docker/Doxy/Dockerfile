FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
	git \
 	doxygen \
	graphviz \
	texlive-latex-extra \
	texlive-plain-generic \
	texlive-fonts-recommended \
	make \
	g++ g++-10 
RUN apt install -y git
RUN rm -rf /var/lib/apt/lists/*
