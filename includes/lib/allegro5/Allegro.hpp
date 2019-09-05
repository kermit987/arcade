//
// Allegro.hpp for  in /home/steven/generique_pacman
//
// Made by Steven Loo Fat
// Login   <loofat_s@epitech.net>
//
// Started on  Thu Mar 31 12:34:33 2016 Steven Loo Fat
// Last update Sun Apr  3 10:43:19 2016 Steven Loo Fat
//

#ifndef ALLEGRO_HPP
# define ALLEGRO_HPP

#include <string>
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include "Data.hpp"
#include "IGui.hpp"

class	Allegro: public IGui
{
public:
  Allegro();
  ~Allegro();
public:
  // virtual bool	createWindow(void) = 0;
  virtual const std::string	&getName(void) const;
  virtual bool			createWindow(int ac, char **av, int width, int height);
  virtual bool			destroyWindow(void);
  virtual bool			refreshWindow(void);
  virtual bool			cleanWindow(void);
  virtual const t_Event&	eventHandler(void);
  virtual bool			drawRect(const t_Rect &);
  virtual bool			drawText(const t_Text &);
  virtual bool                  drawImg(const t_Img &);
  //
  bool				already_load(const std::string &) const;
  bool				add_picture(const std::string &);
  ALLEGRO_BITMAP		*get_right_picture(const std::string &) const;
  //
  typedef struct		s_info
  {
    std::string			name;
    ALLEGRO_BITMAP		*picture;
  }				t_info;
private:
  std::string			lib_name;
  ALLEGRO_DISPLAY		*access_display;
  ALLEGRO_EVENT_QUEUE		*access_queue;
  ALLEGRO_FONT			*access_font;
  ALLEGRO_KEYBOARD_STATE	access_key;
  std::list<t_info*>		access_picture;
};

#endif	// !ALLEGRO_HPP_
