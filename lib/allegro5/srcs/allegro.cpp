//
// allegro.cpp for  in /home/steven/generique_pacman
//
// Made by Steven Loo Fat
// Login   <loofat_s@epitech.net>
//
// Started on  Thu Mar 31 14:03:16 2016 Steven Loo Fat
// Last update Sun Apr  3 23:01:07 2016 Steven Loo Fat
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <list>
#include <iostream>
#include "Allegro.hpp"

extern "C" {
  IGui	*createLib(void)
  {
    return new Allegro();
  }
}

Allegro::Allegro()
{
  this->lib_name = "Allegro";
}

Allegro::~Allegro()
{

}

const std::string	&Allegro::getName(void) const
{
  return (this->lib_name);
}

bool			Allegro::createWindow(int ac, char **av, int width, int height)
{
  (void)ac;
  (void)av;
  (void)width;
  (void)height;
  if (!al_init())
    {
      std::cerr << "Error: init in createWindow failed\n" << std::endl;
      return (false);
    }
  this->access_display = al_create_display((width * 50), (height * 50));
  if (!this->access_display)
    {
      std::cerr << "Error: create_display in createWindow failed" << std::endl;
      return (false);
    }
  if (!al_install_keyboard())
    {
      std::cerr << "failed to initialized the keyboard" << std::endl;
      al_destroy_display(this->access_display);
      return (false);
    }
  if(!al_init_image_addon())
    {
      std::cerr << "Error: failed to load image in create_pacman" << std::endl;
      al_destroy_display(this->access_display);
      return (false);
    }
  if (!al_init_primitives_addon())
    {
      std::cerr << "Error: failed to load al_init_primitives_addon()" << std::endl;
      al_destroy_display(this->access_display);
      return (false);
    }
  al_init_font_addon();		// initialize the font addon
  al_init_ttf_addon();		// initialize the ttf  (True type font) addon
  this->access_queue = al_create_event_queue();
  al_register_event_source(this->access_queue, al_get_keyboard_event_source());
  return (true);
}

bool			Allegro::destroyWindow()
{
  al_destroy_display(this->access_display);
  al_destroy_event_queue(this->access_queue);
  return (true);
}

bool			Allegro::refreshWindow()
{
  al_flip_display();
  return (true);
}

bool			Allegro::cleanWindow()
{
  al_clear_to_color(al_map_rgb(0,0,0));
  return (true);
}

const t_Event&		Allegro::eventHandler()
{
  int			allegro_tab[13];
  t_KeyValue		KeyValue[13];
  t_Event		*event;
  int			i;

  i = 0;
  al_get_keyboard_state(&this->access_key);
  allegro_tab[0] = ALLEGRO_KEY_LEFT;
  allegro_tab[1] = ALLEGRO_KEY_UP;
  allegro_tab[2] = ALLEGRO_KEY_RIGHT;
  allegro_tab[3] = ALLEGRO_KEY_DOWN;
  allegro_tab[4] = ALLEGRO_KEY_ENTER;
  allegro_tab[5] = ALLEGRO_KEY_ESCAPE;
  allegro_tab[6] = ALLEGRO_KEY_DELETE;
  allegro_tab[7] = ALLEGRO_KEY_2;
  allegro_tab[8] = ALLEGRO_KEY_3;
  allegro_tab[9] = ALLEGRO_KEY_4;
  allegro_tab[10] = ALLEGRO_KEY_5;
  allegro_tab[11] = ALLEGRO_KEY_8;
  allegro_tab[12] = ALLEGRO_KEY_9;

  KeyValue[0] = K_LEFT;
  KeyValue[1] = K_UP;
  KeyValue[2] = K_RIGHT;
  KeyValue[3] = K_DOWN;
  KeyValue[4] = K_ENTER;
  KeyValue[5] = K_ESCAPE;
  KeyValue[6] = K_DEL;
  KeyValue[7] = K_2;
  KeyValue[8] = K_3;
  KeyValue[9] = K_4;
  KeyValue[10] = K_5;
  KeyValue[11] = K_8;
  KeyValue[12] = K_9;
  event = new t_Event;
  while (i != 13)
    {
      if (al_key_down(&this->access_key, allegro_tab[i]))
        {
          event->keyValue = KeyValue[i];
          return (*event);
        }
      i++;
    }
  event->keyValue = K_OTHER;
  return (*event);
}

bool		Allegro::drawRect(const t_Rect &var)
{
  ALLEGRO_COLOR	border;
  ALLEGRO_COLOR	filled;

  border.r = var.borderColor.r;	//
  border.g = var.borderColor.g;
  border.b = var.borderColor.b;
  filled.r = var.color.r;
  filled.g = var.color.b;
  filled.b = var.color.b;
  // faire des test avec la fonction suivante
  al_draw_rectangle((var.frame.x * 50), (var.frame.y * 50),
  		    ((var.frame.x + var.frame.w)* 50), ((var.frame.y + var.frame.h)
  							* 50), border, var.borderWidth);
  (void)border;
  al_draw_filled_rectangle((var.frame.x * 50), (var.frame.y * 50),
			   ((var.frame.x + var.frame.w) * 50), ((var.frame.y + var.frame.h)
								* 50), filled);
  // rectangle on va voir ca apres;
  (void)var;
  return (true);
}

bool		Allegro::drawText(const t_Text &var)
{
  ALLEGRO_COLOR	color;

  color.r = var.color.r;
  color.g = var.color.g;
  color.b = var.color.b;
  this->access_font = al_load_ttf_font("police/DancingScript-Bold.ttf", 72,0);
  if (!this->access_font)
    {
      std::cerr << "Couldn't load DancingScript in display_image" << std::endl;
      return (-1);
    }
  al_draw_text(this->access_font, color, var.frame.x * 50, var.frame.y * 50,
	       ALLEGRO_ALIGN_CENTRE, var.text.c_str());
  return (true);
}

bool					Allegro::already_load(const std::string &picture_name) const
{
  std::list<t_info*>::const_iterator	i;

  for (i = this->access_picture.begin(); i != this->access_picture.end(); ++i)
    {
      if (picture_name == (*i)->name)
	return (true);
    }
  return (false);
}

bool		Allegro::add_picture(const std::string &picture_name)
{
  t_info	*picture;

  picture = new t_info;
  picture->name = picture_name;
  picture->picture = al_load_bitmap(picture_name.c_str());
  if (!picture)
    {
      std::cerr << "Error: can't load " << picture_name << std::endl;
      return (false);
    }
  this->access_picture.push_back(picture);
  return (true);
}

ALLEGRO_BITMAP				*Allegro::get_right_picture(const std::string &picture_name) const
{
  std::list<t_info*>::const_iterator	i;

  for (i = this->access_picture.begin(); i != this->access_picture.end(); ++i)
    {
      if (picture_name == (*i)->name)
	(*i)->name;
    }
  return ((*i)->picture);
}

bool			Allegro::drawImg(const t_Img &var)
{
  ALLEGRO_BITMAP	*picture_to_load;

  if (!already_load(var.filename))
    {
      if (!add_picture(var.filename))
	return (false);
    }
  picture_to_load = get_right_picture(var.filename);
  al_draw_bitmap(picture_to_load, var.frame.x, var.frame.y, 1);
  // j'utilise pas toute les info de t_Img;
  return (true);
}
