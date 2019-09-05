##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/libs/ncurses
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 18:18:45 2016 Aurélien METZ Aurélien
## Last update Sun Mar 20 13:51:50 2016 Aurélien METZ Aurélien
##

################################################################################
SRCDIR		=	srcs
HDRDIR		=	../../includes
OBJDIR		=	objs

VPATH		=	$(SRCDIR):$(HDRDIR):$(HDRDIR)/lib/ncurses
################################################################################
CC		=	g++

CXXFLAGS	+=	-Wall -Wextra -Werror -fPIC
CXXFLAGS	+=	$(INCLUDE)
CXXFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

LDFLAGS		=	-l ncurses

DFLAGS		=	-g
OFLAGS		=	-O3

INCLUDE		=	-I $(HDRDIR) -I $(HDRDIR)/lib/ncurses
################################################################################
NAME		=	lib_arcade_ncurses.so

SRCS		=	$(addsuffix .cpp,	ncurses	)
HDRS		=	$(addsuffix .hpp,	IGui	\
						IGame	\
						Ncurses	)

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
