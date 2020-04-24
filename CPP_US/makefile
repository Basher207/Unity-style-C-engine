SHELL := /bin/zsh

Project_directories := $(shell echo ./**/)
Project_Header_includes := $(foreach directory, $(Project_directories), -I $(directory))

mac:
	gcc ./glad.cpp ./src/**/*.cpp -o ./Build/macBuild -F./Framework/ -framework SDL2 $(Project_Header_includes) -std=c++11 -lstdc++
	./Build/macBuild
linux:
	gcc ./glad.cpp ./src/**/*.cpp -o ./Build/linuxBuild -l SDL2 $(Project_Header_includes) -std=c++11 -ldl -Lldl -lm -lstdc++
	./Build/linuxBuild