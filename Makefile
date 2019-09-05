##
## Makefile for  in /home/metz_a/rendu/cpp_arcade
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 17:25:52 2016 Aurélien METZ Aurélien
## Last update Fri Mar 18 20:29:06 2016 Aurélien METZ Aurélien
##

################################################################################
LAUNCHER_DIR	=	launcher
GAMES_DIR	=	games
LIB_DIR		=	lib

LAUNCHER	=	arcade

CP		=	cp
################################################################################
all		:
		$(MAKE) -C $(GAMES_DIR)
		$(MAKE) -C $(LIB_DIR)
		$(MAKE) -C $(LAUNCHER_DIR)
		-$(CP) $(LAUNCHER_DIR)/$(LAUNCHER) .

clean		:
		$(MAKE) -C $(LAUNCHER_DIR) clean
		$(MAKE) -C $(GAMES_DIR) clean
		$(MAKE) -C $(LIB_DIR) clean

fclean		:
		$(MAKE) -C $(LAUNCHER_DIR) fclean
		$(RM) $(LAUNCHER)
		$(MAKE) -C $(GAMES_DIR) fclean
		$(MAKE) -C $(LIB_DIR) fclean

re		:
		$(RM) $(LAUNCHER)
		$(MAKE) -C $(LAUNCHER_DIR) re
		-$(CP) $(LAUNCHER_DIR)/$(LAUNCHER) .
		$(MAKE) -C $(GAMES_DIR) re
		$(MAKE) -C $(LIB_DIR) re

.PHONY		: all clean fclean re
################################################################################
