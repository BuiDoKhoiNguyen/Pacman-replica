
INCLUDES = -ISource/Manager -ISource/Core -ISource/Map -ISource/Menu -ISource/Object -I src/include/SDL2 -L src/lib

CPPS = main.cpp \
		$(wildcard Source/Core/*.cpp)\
		$(wildcard Source/Manager/*.cpp)\
		$(wildcard Source/Map/*.cpp)\
		$(wildcard Source/Menu/*.cpp)\
		$(wildcard Source/Object/*.cpp)

all:
	g++ $(CPPS)  $(INCLUDES)\
	 -o main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
