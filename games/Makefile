##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/games
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 17:39:15 2016 Aurélien METZ Aurélien
## Last update Sun Mar 13 18:03:11 2016 Aurélien METZ Aurélien
##

################################################################################
NIBBLER		=	lib_arcade_nibbler.so
NIBBLER_DIR	=	nibbler

PACMAN		=	lib_arcade_pacman.so
PACMAN_DIR	=	pacman

RM		=	rm -f
CP		=	cp
################################################################################
all			: $(NIBBLER) $(PACMAN)

$(NIBBLER)		:
			$(MAKE) -C $(NIBBLER_DIR)
			-$(CP) $(NIBBLER_DIR)/$(NIBBLER) .

$(PACMAN)		:
			$(MAKE) -C $(PACMAN_DIR)
			-$(CP) $(PACMAN_DIR)/$(PACMAN) .

clean			:
			$(MAKE) -C $(NIBBLER_DIR) clean
			$(MAKE) -C $(PACMAN_DIR) clean

fclean			:
			$(MAKE) -C $(NIBBLER_DIR) fclean
			$(MAKE) -C $(PACMAN_DIR) fclean
			$(RM) $(NIBBLER)
			$(RM) $(PACMAN)

re			:
			$(RM) $(NIBBLER)
			$(RM) $(PACMAN)
			$(MAKE) -C $(NIBBLER_DIR) re
			$(MAKE) -C $(PACMAN_DIR) re
			-$(CP) $(NIBBLER_DIR)/$(NIBBLER) .
			-$(CP) $(PACMAN_DIR)/$(PACMAN) .

.PHONY			: all clean fclean re
################################################################################
