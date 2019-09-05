##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/libs/allegro5
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 18:13:17 2016 Aurélien METZ Aurélien
## Last update Sun Apr  3 23:04:37 2016 Steven Loo Fat
##

################################################################################
SRCDIR		=	srcs
HDRDIR		=	../../includes
OBJDIR		=	objs
LIBDIR		=	libs

VPATH		=	$(SRCDIR):$(HDRDIR):$(HDRdIR)/lib/allegro5:$(LIBDIR)
################################################################################
CC		=	g++

CXXFLAGS	+=	-Wall -Wextra -Werror -fPIC
CXXFLAGS	+=	$(INCLUDE)
CXXFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

LDFLAGS		=	-L $(LIBDIR) -lallegro_acodec -lallegro_audio		\
			-lallegro_color -lallegro_dialog -lallegro_font 	\
			-lallegro_image -lallegro_main -lallegro_memfile	\
			-lallegro_physfs -lallegro_primitives -lallegro_ttf

DFLAGS		=	-g
OFLAGS		=	-O3

INCLUDE		=	-I $(HDRDIR) -I $(HDRDIR)/lib/allegro5
################################################################################
NAME		=	lib_arcade_allegro5.so

SRCS		=	$(addsuffix .cpp,	allegro	)
HDRS		=	$(addsuffix .hpp,	IGui		)

OBJS		=	$(SRCS:%.cpp=$(OBJDIR)/%.o)
################################################################################
all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) -shared $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o:	%.cpp $(HDRS)
		$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.SUFFIXES:	.cpp .o

.PHONY:		all clean fclean re
################################################################################
