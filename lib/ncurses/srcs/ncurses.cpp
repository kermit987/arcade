//
// ncurses.cpp for  in /home/metz_a/rendu/cpp_arcade
// 
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
// 
// Started on  Tue Mar 29 15:58:25 2016 Aurélien METZ Aurélien
// Last update Sat Apr  2 11:41:56 2016 Aurélien METZ Aurélien
//

#include "Ncurses.hpp"

extern "C" { IGui	*createLib(void) { return new Ncurses(); } }

bool	Ncurses::createWindow(int, char **, int, int)
{
  if (initscr() == NULL
      || cbreak() == ERR
      || noecho() == ERR
      || nodelay(stdscr, TRUE) == ERR
      || keypad(stdscr, TRUE) == ERR
      || start_color() == ERR
      || curs_set(0) == ERR
      || init_pair(1, COLOR_RED, COLOR_BLACK) == ERR
      || init_pair(2, COLOR_GREEN, COLOR_BLACK) == ERR
      || init_pair(3, COLOR_YELLOW, COLOR_BLACK) == ERR
      || init_pair(4, COLOR_BLUE, COLOR_BLACK) == ERR
      || init_pair(5, COLOR_MAGENTA, COLOR_BLACK) == ERR
      || init_pair(6, COLOR_CYAN, COLOR_BLACK) == ERR
      || init_pair(7, COLOR_WHITE, COLOR_BLACK) == ERR
      || init_pair(8, COLOR_BLACK, COLOR_BLACK) == ERR)
    return false;
  return true;
}

bool	Ncurses::destroyWindow(void)
{
  return endwin() == OK;
}

bool	Ncurses::refreshWindow(void)
{
  return refresh() == OK;
}

bool	Ncurses::cleanWindow(void)
{
  return clear() == OK;
}

const t_Event&	Ncurses::eventHandler(void)
{
  int		ch = getch();

  event.keyType = EV_KDOWN;
  switch ( ch ) {
  case 27:
    event.keyValue = K_ESCAPE;
    break;
  case '\n':
    event.keyValue = K_ENTER;
    break;
  case KEY_BACKSPACE:
    event.keyValue = K_DEL;
    break;
  case KEY_UP:
    event.keyValue = K_UP;
    break;
  case KEY_DOWN:
    event.keyValue = K_DOWN;
    break;
  case KEY_LEFT:
    event.keyValue = K_LEFT;
    break;
  case KEY_RIGHT:
    event.keyValue = K_RIGHT;
    break;
  default:
    event.keyValue = K_OTHER;
    break;
  }
  event.charName = ch;
  return event;
}

bool	Ncurses::drawRect(const t_Rect &r)
{
  color_set(r.borderColor.colorNc, NULL);
  for (int x = r.frame.x + 1; x < r.frame.x + r.frame.w - 1; x++) {
    mvaddch(r.frame.y, x, r.hBorderChar);
    mvaddch(r.frame.y + r.frame.h - 1, x, r.hBorderChar);
  }
  for (int y = r.frame.y; y < r.frame.y + r.frame.h; y++) {
    mvaddch(y, r.frame.x, r.vBorderChar);
    mvaddch(y, r.frame.x + r.frame.w - 1, r.vBorderChar);
  }
  color_set(r.color.colorNc, NULL);
  for (int x = r.frame.x + 1; x < r.frame.x + r.frame.w - 1; x++)
    for (int y = r.frame.y + 1; y < r.frame.y + r.frame.h - 1; y++)
      mvaddch(y, x, ' ');
  return true;
}

bool	Ncurses::drawText(const t_Text &t)
{
  color_set(t.color.colorNc, NULL);
  mvprintw(t.frame.y, t.frame.x, t.text.c_str());
  return true;
}

bool	Ncurses::drawImg(const t_Img &i)
{
  color_set(i.color.colorNc, NULL);
  for (int y = 0; y < i.frame.y; y++)
    for (int x = 0; x < i.frame.x; x++)
      mvaddch(y, x, i.ncImg[(y * i.frame.w) + x]);
  return true;
}
