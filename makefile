
NAME = AB
SRCS =	srcs/*.cpp srcs/ability/*.cpp srcs/ability/animation/*.cpp srcs/ability/objects/*.cpp \
		srcs/ability/selectors/*.cpp srcs/ability/switches/*.cpp srcs/battle/*.cpp \
		srcs/battle/turn/*.cpp srcs/characters/*.cpp srcs/effects/*.cpp srcs/objects/*.cpp \
		srcs/tools/*.cpp srcs/UI/*.cpp srcs/info/*.cpp

OBJ = $(SRCS:.c=.o)
HDR =	-I ./hdr -I ./hdr/battleClasses -I ./hdr/particle -I ./hdr/render -I ./hdr/tools -I ./hdr/UI \
		-I ./hdr/abilities -I ./hdr/abilities/objects -I ./hdr/ability/animation -I ./hdr/objects -I ./hdr/ability \
		-I ./hdr/abilities/selectors/ -I ./hdr/info/

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