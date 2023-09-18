
NAME = AB

SRCS =	srcs/main.cpp srcs/UI/bar.cpp srcs/UI/battleUI.cpp srcs/UI/button.cpp srcs/UI/energy.cpp srcs/UI/number.cpp srcs/UI/statuses.cpp \
		srcs/tools/basicTools.cpp srcs/tools/init.cpp srcs/tools/mapTools.cpp srcs/tools/poller.cpp srcs/tools/renderer.cpp \
		srcs/tools/screenShaker.cpp srcs/tools/utility.cpp srcs/objects/object.cpp srcs/info/counter.cpp \
		srcs/info/info.cpp srcs/effects/dust.cpp srcs/effects/particle.cpp srcs/effects/partManager.cpp \
		srcs/characters/Character.cpp srcs/characters/CharacterTools.cpp srcs/characters/hoverOver.cpp srcs/characters/Kill.cpp \
		srcs/battle/battleGround.cpp srcs/battle/battleMoving.cpp srcs/battle/hoverChecker.cpp srcs/battle/moveCharacter.cpp \
		srcs/battle/moveLine.cpp srcs/battle/movingAlgos.cpp srcs/battle/turn/turnIndicator.cpp srcs/battle/turn/turnOrder.cpp \
		srcs/ability/abilities.cpp srcs/ability/chanceChecks.cpp srcs/ability/characterMover.cpp srcs/ability/effectUpdater.cpp \
		srcs/ability/groundColoring.cpp srcs/ability/switches/pyroUpdates.cpp srcs/ability/switches/thiefUpdates.cpp \
		srcs/ability/selectors/allSelector.cpp srcs/ability/selectors/Markers.cpp srcs/ability/selectors/multiSelector.cpp \
		srcs/ability/selectors/Selector.cpp srcs/ability/selectors/SelectorForTiles.cpp srcs/ability/objects/dagger.cpp \
		srcs/ability/objects/fireBall.cpp srcs/ability/objects/smokeBomb.cpp srcs/ability/objects/smokeEffect.cpp \
		srcs/ability/damages/damageCreator.cpp srcs/ability/damages/Damager.cpp \
		srcs/ability/animation/daggerSlashAnim.cpp srcs/ability/animation/daggerThrowAnim.cpp srcs/ability/animation/flameBlast.cpp \
		srcs/ability/animation/flamePortAnim.cpp srcs/ability/animation/flameSlashAnim.cpp srcs/ability/animation/incinerateAnim.cpp \
		srcs/ability/animation/smokeBombAnim.cpp srcs/ability/animation/lionSmackAnim.cpp srcs/ability/switches/lionUpdates.cpp \
		srcs/characters/StatusUpdater.cpp srcs/info/stunUpdates.cpp srcs/ability/selectors/phantomSelector.cpp \
		srcs/ability/animation/phantomAnim.cpp srcs/ability/objects/phantomKnight.cpp srcs/ability/animation/rotate.cpp \
		srcs/ability/switches/updateRotate.cpp srcs/info/control.cpp srcs/info/controlSetter.cpp srcs/ability/damages/opportunity.cpp \
		srcs/info/movementEnergy.cpp srcs/info/infoBar.cpp srcs/UI/UIText.cpp srcs/UI/fatigueBar.cpp srcs/info/snippet.cpp \
		srcs/info/flyingText.cpp srcs/tools/textTools.cpp srcs/objects/toolBox.cpp srcs/objects/objUpdate.cpp \
		srcs/ability/animation/HammerSmack.cpp srcs/ability/switches/smithUpdates.cpp srcs/tools/soundSystem.cpp \
		srcs/info/supplyEffect.cpp srcs/tools/throwArch.cpp srcs/ability/animation/toolThrowAnim.cpp srcs/ability/animation/supplyAlly.cpp \
		srcs/objects/toolBoxOnGround.cpp srcs/ability/animation/pickUpToolBox.cpp srcs/ability/animation/supply.cpp \
		srcs/objects/toolBoxNumber.cpp srcs/ability/animation/genericToolThrow.cpp srcs/ability/animation/smithBuff.cpp

OBJ = $(SRCS:.cpp=.o)
HDR =	-I ./hdr -I ./hdr/battleClasses -I ./hdr/particle -I ./hdr/render -I ./hdr/tools -I ./hdr/UI \
		-I ./hdr/abilities -I ./hdr/abilities/objects -I ./hdr/ability/animation -I ./hdr/objects -I ./hdr/ability \
		-I ./hdr/abilities/selectors/ -I ./hdr/info/ -I ./hdr/ability/damages/ -I ./hdr/effects

FLAGS = -std=c++11
CGFLAGS = 
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Versions/A/Headers \
				-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				 \
				-framework SDL2 -framework SDL2_image \
				-framework SDL2_mixer \
				-framework SDL2_ttf

all: $(NAME)

$(NAME): $(OBJ)
	@g++ $(FLAGS) $(CGFLAGS) $(FRAMEWORKS) $(OBJ) -o $(NAME)

.cpp.o:
		@g++ $(FLAGS) $(INCLUDES) $(HDR) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
