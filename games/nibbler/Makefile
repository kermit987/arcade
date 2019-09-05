##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/games/nibbler
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 17:58:57 2016 Aurélien METZ Aurélien
## Last update Sun Apr  3 22:29:15 2016 Clementine
##

################################################################################
SRCDIR		=	srcs
HDRDIR		=	../../includes
OBJDIR		=	objs
LIBDIR		=	libs

VPATH		=	$(SRCDIR):$(HDRDIR):$(HDRDIR)/games/nibbler:$(LIBDIR)
################################################################################
CC		=	g++

CXXFLAGS	+=	-Wall -Wextra -Werror -fPIC -std=c++11
CXXFLAGS	+=	$(INCLUDE)
CXXFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

DFLAGS		=	-g
OFLAGS		=	-O3

INCLUDE		=	-I $(HDRDIR) -I $(HDRDIR)/games/nibbler
################################################################################
NAME		=	lib_arcade_nibbler.so

SRCS		=	$(addsuffix .cpp,	Nibbler	)
HDRS		=	$(addsuffix .hpp,	Protocol	\
						IGame		\
						IGui		)

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
