# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 15:51:16 by vkuusela          #+#    #+#              #
#    Updated: 2025/05/14 11:28:14 by vkuusela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= raytracer
CC 				= c++
CFLAGS 			= -Wall -Wextra -Werror -std=c++20 -Ivendored/SDL/include/
OFLAGS			= -O3 -flto -march=native
RM 				= rm -rf

SDL				= vendored/SDL/build/libSDL3.a

SOURCES			= src/main.cpp src/Window.cpp src/Renderer.cpp src/Texture.cpp \
				  src/Application.cpp src/AHittable.cpp src/Ray.cpp src/Sphere.cpp \
				  src/Vec3.cpp src/Camera.cpp src/ALight.cpp src/BlinnPhongMaterial.cpp \
				  src/PointLight.cpp src/AmbientLight.cpp src/Scene.cpp src/HitRecord.cpp \
				  src/Quaternion.cpp

OBJDIR			= obj

HEADERS			= inc/Window.hpp inc/Renderer.hpp inc/Texture.hpp inc/Application.hpp \
				  inc/AHittable.hpp inc/Ray.hpp inc/Sphere.hpp inc/Vec3.hpp inc/Camera.hpp \
				  inc/ALight.hpp inc/PointLight.hpp inc/IMaterial.hpp \
				  inc/BlinnPhongMaterial.hpp inc/AmbientLight.hpp inc/Scene.hpp \
				  inc/HitRecord.hpp inc/Quaternion.hpp

OBJECTS			= $(SOURCES:%.cpp=$(OBJDIR)/%.o)

$(OBJDIR)/%.o:			%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@

all: 			$(NAME)

$(NAME):		$(SDL) $(OBJECTS) $(HEADERS)
	@echo -n "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OFLAGS) $(OBJECTS) $(SDL) -o $(NAME)
	@echo " Done."

$(SDL):
	@echo -n "Building SDL3..."
	@mkdir -p vendored/SDL/build
	@(cd vendored/SDL && cmake -S . -B build -DSDL_STATIC=TRUE && cmake --build build -j4)
	@echo " Done."

clean:
	@echo -n "Cleaning .o files..."
	@$(RM) $(OBJECTS) $(OBJDIR)
	@echo " Done."

fclean:			clean
	@echo -n "Full clean..."
	@$(RM) $(NAME)
	@$(RM) $(SDL)
	@echo " Done."

re:				fclean all

debug:			CFLAGS += -g
debug:			re

fsanitize:		CFLAGS += -g -fsanitize=address
fsanitize:		re

gprof:			CFLAGS += -g -pg
gprof:			re

.PHONY:			all clean fclean re debug fsanitize gprof
