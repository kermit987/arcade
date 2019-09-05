/*
** IGui.hpp for  in /home/clementine/rendu/arcade/cpp_arcade
** 
** Made by Clementine
** Login   <clementine@epitech.net>
** 
** Started on  Sun Apr  3 23:37:40 2016 Clementine
** Last update Sun Apr  3 23:37:41 2016 Clementine
*/

#ifndef IGUI_HPP_
# define IGUI_HPP_

# include <string>
# include "Data.hpp"

class	IGui
{
public:
  IGui(void) {}
  virtual ~IGui(void) {}
  // virtual bool	createWindow(void) = 0;
  virtual const std::string	&getName(void) const = 0;
  virtual bool			createWindow(int ac, char **av, int width, int height) = 0;
  virtual bool			destroyWindow(void) = 0;
  virtual bool			refreshWindow(void) = 0;
  virtual bool			cleanWindow(void) = 0;
  virtual const t_Event&	eventHandler(void) = 0;
  virtual bool			drawRect(const t_Rect &) = 0;
  virtual bool			drawText(const t_Text &) = 0;
  virtual bool                  drawImg(const t_Img &) = 0;
};

typedef IGui	*(*t_GuiCreator)(void);

#endif /* !IGUI_HPP_ */
