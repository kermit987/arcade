/*
** Lapin.hpp for Lapin in /home/clementine/rendu/arcade
** 
** Made by Clementine
** Login   <clementine@clementine>
** 
** Started on  Sat Mar 19 04:52:21 2016 Clementine
** Last update Sun Apr  3 22:20:41 2016 Clementine
*/

#ifndef LAPIN_HPP_
# define LAPIN_HPP_

# define FREQUENCE 7
# define UNITE 40
# define WALL_WIDTH 160
# define WALL_HEIGHT 40

#include <lapin.h>
#include <list>
#include <map>
#include "IGui.hpp"

class Lapin : public IGui
{
public:
  Lapin();
  virtual ~Lapin() {};

  /* WINDOW EVENT */
  
  virtual bool createWindow(int ac, char **av, int width, int height);
  virtual bool destroyWindow(void);
  virtual bool refreshWindow(void);
  virtual bool cleanWindow(void);
  
  /* GETTER */
  
  virtual const std::string	&getName(void) const;
  
  /* EVENT */
  
  virtual const t_Event	&eventHandler(void);

  /* DRAWING */
  
  virtual bool drawImg(const t_Img &);
  virtual bool drawRect(const t_Rect &);
  virtual bool drawText(const t_Text &);

private:
  t_bunny_window		*win;
  t_Event			key;
  int				direction;
  std::string			name;

  std::map<std::string, t_bunny_picture*>		_img;
  
  /* EVENT */

  t_bunny_response		refreshEvent(void *data);
  static t_bunny_response	IntermediaireLoopFunction(void *);
  static t_bunny_response	IntermediaireKeyFunction(t_bunny_event_state state, t_bunny_keysym key, void *);
  t_bunny_response		keyHandler(t_bunny_event_state state, t_bunny_keysym key, void *);
  static t_bunny_response	BunnyDisplay(void *data);
};

#endif /* !LAPIN_HPP_ */
