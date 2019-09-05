//
// Ncurses.hpp for  in /home/metz_a/rendu/cpp_arcade/lib/ncurses
// 
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
// 
// Started on  Sun Mar 20 13:08:23 2016 Aurélien METZ Aurélien
// Last update Thu Mar 31 14:20:12 2016 Aurélien METZ Aurélien
//

#ifndef NCURSES_HPP_
# define NCURSES_HPP_

# include "IGui.hpp"
# include <curses.h>

class	Ncurses : public IGui
{
public:
  Ncurses(void): IGui(), name("Ncurses") {}
  virtual ~Ncurses(void) {}
  virtual const std::string&	getName(void) const { return name; }
  virtual bool			createWindow(int, char **, int, int);
  virtual bool			destroyWindow(void);
  virtual bool			refreshWindow(void);
  virtual bool			cleanWindow(void);
  virtual const t_Event&	eventHandler(void);
  virtual bool			drawRect(const t_Rect &);
  virtual bool			drawText(const t_Text &);
  virtual bool			drawImg(const t_Img &);
private:
  t_Event			event;
  std::string			name;
};

#endif /* !NCURSES_HPP_ */
