
NAME = AB
SRCS =  srcs/main.cpp srcs/tools/basicTools.cpp srcs/tools/poller.cpp srcs/tools/renderer.cpp \
		srcs/tools/init.cpp srcs/battle/battleGround.cpp srcs/battle/battleMoving.cpp \
		srcs/battle/movingAlgos.cpp srcs/battle/hoverChecker.cpp srcs/battle/moveLine.cpp \
		srcs/battle/moveCharacter.cpp srcs/characters/Character.cpp srcs/effects/dust.cpp \
		srcs/battle/turn/turnOrder.cpp srcs/battle/turn/turnIndicator.cpp srcs/characters/Kill.cpp \
		srcs/effects/particle.cpp srcs/effects/partManager.cpp srcs/UI/bar.cpp srcs/UI/battleUI.cpp \
		srcs/tools/utility.cpp srcs/UI/button.cpp srcs/UI/energy.cpp srcs/ability/groundColoring.cpp \
		srcs/tools/mapTools.cpp srcs/ability/animation/daggerThrowAnim.cpp srcs/ability/characterMover.cpp\
		srcs/characters/hoverOver.cpp srcs/ability/objects/dagger.cpp srcs/ability/damageCreator.cpp \
		srcs/objects/object.cpp srcs/tools/screenShaker.cpp srcs/ability/abilities.cpp \
		srcs/ability/Selector.cpp srcs/ability/chanceChecks.cpp

OBJ = $(SRCS:.c=.o)
HDR =	-I ./hdr -I ./hdr/battleClasses -I ./hdr/particle -I ./hdr/render -I ./hdr/tools -I ./hdr/UI \
		-I ./hdr/abilities -I ./hdr/abilities/objects -I ./hdr/ability/animation -I ./hdr/objects -I ./hdr/ability
FLAGS = -std=c++11
CGFLAGS = 
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Versions/A/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				 \
				-framework SDL2 -framework SDL2_image \
				-framework SDL2_mixer

all: $(NAME)

$(NAME): $(OBJ)
	@g++ $(FLAGS) $(CGFLAGS) $(FRAMEWORKS) $(OBJ) -o $(NAME)

.c.o: $(HEADERS)
		@g++ $(FLAGS) $(INCLUDES) $(HDR) -c $< -o $@

clean:
	@rm -rf $(NAME)

fclean:
	@rm -rf $(NAME)

re: fclean all