##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/launcher
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Tue Mar 15 16:49:16 2016 Aurélien METZ Aurélien
## Last update Sun Mar 20 15:14:35 2016 Aurélien METZ Aurélien
##

################################################################################
SRCDIR		=	srcs
HDRDIR		=	../includes
OBJDIR		=	objs

VPATH		=	$(SRCDIR):$(HDRDIR):$(HDRDIR)/launcher
################################################################################
CC		=	g++

CXXFLAGS	+=	-Wall -Wextra -Werror
CXXFLAGS	+=	$(INCLUDE)
CXXFLAGS	+=	$(if $(DF), $(DFLAGS), $(OFLAGS))

LDFLAGS		=	-l dl

DFLAGS		=	-g
OFLAGS		=	-O3

INCLUDE		=	-I $(HDRDIR) -I $(HDRDIR)/launcher
################################################################################
NAME		=	arcade

SRCS		=	$(addsuffix .cpp,	main	\
						Menu	)
HDRS		=	$(addsuffix .hpp,	IGui		\
						IGame		\
						ErrorManagment	\
						Objext		\
						Menu		)

OBJS		=	$(SRCS:%.cpp=$(OBJDIR)/%.o)
################################################################################
all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

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
