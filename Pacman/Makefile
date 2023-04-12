
INCLUDES = -ISource/Manager -ISource/Core -ISource/Map -ISource/Menu -ISource/Object -I src/include/SDL2 -L src/lib

CPPS = main.cpp \
          Source\Core\Engine.cpp \
		  Source\Core\PlayStateManager.cpp \
		  Source\Core\Window.cpp \
		  Source\Manager\GameManager.cpp \
		  Source\Manager\SoundManager.cpp \
		  Source\Manager\TextManager.cpp \
		  Source\Manager\TickManager.cpp \
		  Source\Map\Map.cpp \
		  Source\Menu\Button.cpp \
		  Source\Menu\Menu.cpp \
		  Source\Object\Ghost.cpp \
		  Source\Object\Item.cpp \
		  Source\Object\Object.cpp \
		  Source\Object\Pacman.cpp \
		  Source\Object\TextureSrc.cpp \

all:
	g++ $(CPPS)  $(INCLUDES)\
	 -o main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
