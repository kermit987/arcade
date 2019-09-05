##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/libs/lapin
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 18:17:47 2016 Aurélien METZ Aurélien
## Last update Sun Apr  3 22:42:10 2016 Clementine
##

################################################################################
SRCDIR		=	srcs
HDRDIR		=	../../includes
OBJDIR		=	objs
LIBDIR		=	libs

VPATH		=	$(SRCDIR):$(HDRDIR):$(HDRDIR)/lib/lapin:$(LIBDIR)
################################################################################
CC		=	g++

CXXFLAGS	+=	-Wall -Wextra -Werror -fPIC -std=c++11
CXXFLAGS	+=	$(INCLUDE)
CXXFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

LDFLAGS		=	-L $(LIBDIR) -llapin -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lstdc++ -ldl -lm

DFLAGS		=	-g
OFLAGS		=	-O3

INCLUDE		=	-I $(HDRDIR) -I $(HDRDIR)/lib/lapin
################################################################################
NAME		=	lib_arcade_lapin.so

SRCS		=	$(addsuffix .cpp,	Lapin	)
HDRS		=	$(addsuffix .hpp,	IGui	)

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
