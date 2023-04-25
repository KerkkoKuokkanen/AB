
NAME = AB
SRCS =  srcs/main.cpp srcs/tools/basicTools.cpp srcs/tools/poller.cpp srcs/tools/renderer.cpp \
		srcs/tools/init.cpp srcs/battle/battleGround.cpp srcs/battle/battleMoving.cpp \
		srcs/characters/Character.cpp

OBJ = $(SRCS:.c=.o)
HDR = -I ./hdr -I ./hdr/classes
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