##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/games/pacman
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 17:47:25 2016 Aurélien METZ Aurélien
## Last update Sun Apr  3 18:00:17 2016 Steven Loo Fat
##

################################################################################
SRCDIR		=	srcs
HDRDIR		=	../../includes
OBJDIR		=	objs
LIBDIR		=	libs

VPATH		=	$(SRCDIR):$(HDRDIR):$(HDRDIR)/games/pacman:$(LIBDIR)
################################################################################
CC		=	g++

CXXFLAGS	+=	-Wall -Wextra -Werror -fPIC -std=c++11
CXXFLAGS	+=	$(INCLUDE)
CXXFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

DFLAGS		=	-g
OFLAGS		=	-O3

INCLUDE		=	-I $(HDRDIR) -I $(HDRDIR)/games/pacman
################################################################################
NAME		=	lib_arcade_pacman.so

SRCS		=	$(addsuffix .cpp,	pacman	)
HDRS		=	$(addsuffix .hpp,	)

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
