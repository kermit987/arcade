/*
** Lapin.cpp for Lapin in /home/clementine/rendu/arcade
** 
<** Made by Clementine
** Login   <clementine@clementine>
** 
** Started on  Sat Mar 19 04:56:26 2016 Clementine
** Last update Sun Apr  3 22:58:00 2016 Clementine
*/

#include <iostream>
#include <fstream>
#include "Lapin.hpp"

extern "C" {
  IGui	*createLib(void)
  {
    return new Lapin();
  }
}

Lapin::Lapin()
{
  direction = 0;
  name = "lapin";
  bunny_set_loop_main_function(IntermediaireLoopFunction);
  bunny_set_key_response(IntermediaireKeyFunction);
}

const std::string &Lapin::getName(void) const
{
  return name;
}

bool Lapin::createWindow(int, char **, int width, int height)
{
  win = bunny_start(width * 40, height * 40, false, "Arcade");
  return true;
}

bool Lapin::destroyWindow(void)
{
  bunny_stop(win);
  return true;
}

t_bunny_response Lapin::keyHandler(t_bunny_event_state state, t_bunny_keysym t_key, void *)
{
  if (state == GO_UP)
    {
      switch (static_cast<int>(t_key))
      	{
      	case static_cast<int>(BKS_RIGHT):
	  direction = 0;
	  break;
      	case static_cast<int>(BKS_LEFT):
	  direction = 1;
	  break;
      	case static_cast<int>(BKS_UP):
	  direction = 2;
	  break;
      	case static_cast<int>(BKS_DOWN):
	  direction = 3;
	  break;
      	case static_cast<int>(BKS_ESCAPE):
      	  direction = -1;
	  break;
	case static_cast<int>(BKS_5):
	  direction = 5;
	  break;
	case static_cast<int>(BKS_8):
	  direction = 8;
	  break;
      	}
    }
  return GO_ON;
}

t_bunny_response Lapin::refreshEvent(void *)
{
  switch (direction)
    {
    case 0:
      key.set(EV_KUP, K_RIGHT, 'r');
      break;
    case 1:
      key.set(EV_KUP, K_LEFT, 'l');
      break;
    case 2:
      key.set(EV_KUP, K_UP, 'u');
      break;
    case 3:
      key.set(EV_KUP, K_DOWN, 'd');
      break;
    case -1:
      key.set(EV_KUP, K_ESCAPE, 'x');
      break;
    // case 8:
    //   key.set(EV_KUP, K_8, '8');
    //   break;
    // case 5:
    //   key.set(EV_KUP, K_5, '5');
    //   break;
    }
  return GO_ON;
}

t_bunny_response Lapin::IntermediaireLoopFunction(void *data)
{
  Lapin *bunny;

  bunny = static_cast<Lapin *>(data);
  bunny->refreshEvent(static_cast<void *>(data));
  return EXIT_ON_SUCCESS;
}

t_bunny_response Lapin::IntermediaireKeyFunction(t_bunny_event_state state, t_bunny_keysym key, void *data)
{
  Lapin *bunny;

  bunny = static_cast<Lapin *>(data);
  return bunny->keyHandler(state, key, static_cast<void *>(data));
}

t_bunny_response Lapin::BunnyDisplay(void *data)
{
  t_bunny_window	*win = static_cast<t_bunny_window *>(data);

  bunny_display(win);
  return GO_ON;
}

bool Lapin::refreshWindow(void)
{
  bunny_display(win);
  bunny_loop(win, FREQUENCE, this);
  return true;
}

const t_Event &Lapin::eventHandler(void)
{
  return (key);
}

bool Lapin::drawImg(const t_Img &image)
{
  t_bunny_picture *img;
  t_bunny_position pos;
  std::map<std::string, t_bunny_picture*>::iterator it = _img.begin();
  
  while (it != _img.end())
    {
      if (it->first == image.filename)
	break;
      ++it;
    }
  if (it == _img.end())
    {
      img = bunny_load_picture(image.filename.c_str());
      _img.insert(std::pair<std::string, t_bunny_picture*>(image.filename, img));
      ++it;
    }

  pos.x = image.frame.x * 40;
  pos.y = image.frame.y * 40;
  (*it).second->clip_x_position = 0;
  (*it).second->clip_y_position = 0;
  (*it).second->clip_width = image.frame.w * 40;
  (*it).second->clip_height = image.frame.h * 40;
  bunny_draw((*it).second);
  bunny_blit(&win->buffer, (*it).second, &pos);
  return true;
}

bool Lapin::drawRect(const t_Rect &rect)
{
  t_bunny_picture *fRect;
  t_bunny_picture *sRect;
  t_bunny_position fPos;
  t_bunny_position sPos;
  unsigned int fColor;
  unsigned int sColor;

  fColor = (rect.color.r << 16) + (rect.color.g << 8) + rect.color.b;
  sColor = (rect.borderColor.r << 16) + (rect.borderColor.g << 8) + rect.borderColor.b;

  fRect = bunny_new_picture(rect.frame.w, rect.frame.h);
  sRect = bunny_new_picture(rect.frame.w - (rect.borderWidth * 2), rect.frame.h - (rect.borderWidth * 2));

  fColor = ALPHA(rect.color.a, fColor);
  sColor = ALPHA(rect.borderColor.a, sColor);
  
  fPos.x = rect.frame.x * 40;
  fPos.y = rect.frame.y * 40;
  sPos.x = (rect.frame.x + rect.borderWidth) * 40;
  sPos.y = (rect.frame.y + rect.borderWidth) * 40;

  fRect->clip_x_position = 0;
  fRect->clip_y_position = 0;
  fRect->clip_width = rect.frame.w * 40;
  fRect->clip_height = rect.frame.h * 40;

  sRect->clip_x_position = 0;
  sRect->clip_y_position = 0;
  sRect->clip_width = rect.frame.w * 40;
  sRect->clip_height = rect.frame.h * 40;

  bunny_fill(&fRect->buffer, fColor);
  bunny_fill(&sRect->buffer, sColor);

  bunny_draw(fRect);
  bunny_draw(sRect);

  bunny_blit(&win->buffer, fRect, &fPos);
  bunny_blit(&win->buffer, sRect, &sPos);
  return true;
}

bool Lapin::drawText(const t_Text &)
{
  return true;
}

bool Lapin::cleanWindow()
{
  bunny_clear(&win->buffer, 0x000000);
  return true;
}
