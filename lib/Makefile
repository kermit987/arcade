##
## Makefile for  in /home/metz_a/rendu/cpp_arcade/games
## 
## Made by Aurélien METZ Aurélien
## Login   <metz_a@epitech.net>
## 
## Started on  Sun Mar 13 17:39:15 2016 Aurélien METZ Aurélien
## Last update Wed Mar 16 15:43:51 2016 Aurélien METZ Aurélien
##

################################################################################
NCURSES		=	lib_arcade_ncurses.so
NCURSES_DIR	=	ncurses

ALLEGRO5	=	lib_arcade_allegro5.so
ALLEGRO5_DIR	=	allegro5

LAPIN		=	lib_arcade_lapin.so
LAPIN_DIR	=	lapin

RM		=	rm -f
CP		=	cp
################################################################################
all			: $(NCURSES) $(ALLEGRO5) $(LAPIN)

$(NCURSES)		:
			$(MAKE) -C $(NCURSES_DIR)
			-$(CP) $(NCURSES_DIR)/$(NCURSES) .

$(ALLEGRO5)		:
			$(MAKE) -C $(ALLEGRO5_DIR)
			-$(CP) $(ALLEGRO5_DIR)/$(ALLEGRO5) .

$(LAPIN)		:
			$(MAKE) -C $(LAPIN_DIR)
			-$(CP) $(LAPIN_DIR)/$(LAPIN) .

clean			:
			$(MAKE) -C $(NCURSES_DIR) clean
			$(MAKE) -C $(ALLEGRO5_DIR) clean
			$(MAKE) -C $(LAPIN_DIR) clean

fclean			:
			$(MAKE) -C $(NCURSES_DIR) fclean
			$(MAKE) -C $(ALLEGRO5_DIR) fclean
			$(MAKE) -C $(LAPIN_DIR) fclean
			$(RM) $(NCURSES)
			$(RM) $(ALLEGRO5)
			$(RM) $(LAPIN)

re			:
			$(RM) $(NCURSES)
			$(RM) $(ALLEGRO5)
			$(RM) $(LAPIN)
			$(MAKE) -C $(NCURSES_DIR) re
			$(MAKE) -C $(ALLEGRO5_DIR) re
			$(MAKE) -C $(LAPIN_DIR) re
			-$(CP) $(NCURSES_DIR)/$(NCURSES) .
			-$(CP) $(ALLEGRO5_DIR)/$(ALLEGRO5) .
			-$(CP) $(LAPIN_DIR)/$(LAPIN) .

.PHONY			: all clean fclean re
################################################################################
