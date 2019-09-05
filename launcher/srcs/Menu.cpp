//
// Menu.cpp for  in /home/metz_a/rendu/cpp_arcade
// 
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
// 
// Started on  Fri Mar 18 19:35:29 2016 Aurélien METZ Aurélien
// Last update Sat Apr  2 21:58:12 2016 Aurélien METZ Aurélien
//

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <glob.h>
#include "ErrorManagment.hpp"
#include "Menu.hpp"

Menu::Menu()
{

  try {
    findLibs(&lLib, "lib/", "lib/lib_arcade_*.so");
    lib = lLib.begin();
    findLibs(&lGame, "games/", "games/lib_arcade_*.so");
    game = lGame.begin();
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}

template<typename T>
static void	freeElem(Objext<T> *obj) { delete obj; }

Menu::~Menu()
{
  for_each(lGame.begin(), lGame.end(), freeElem<IGame *>);
  for_each(lLib.begin(), lLib.end(), freeElem<IGui *>);
}

void		Menu::start(IGui *_gui)
{
  gui = _gui;
  if (gui->createWindow(0, NULL, 75, 50) == false)
    throw ErrGui(gui->getName(), "Could not create a window");
  displayBackGround();
  displayName();
  chooseName();
  chooseGame();
  chooseGui();
  if (gui->destroyWindow() == false)
    throw ErrGui(gui->getName(), "Could not destroy the window properly");
}

const std::string&	Menu::getName() const { return name; }

const std::vector<Objext<IGame *> *>::iterator&	Menu::getGame() const { return game; }

const std::vector<Objext<IGui *> *>::iterator&	Menu::getLib() const { return lib; }

void	Menu::nextGame()
{
  ++game;
  if (game == lGame.end())
    game = lGame.begin();
}

void	Menu::prevGame()
{
  if (game == lGame.begin())
    game = lGame.end();
  --game;
}

void	Menu::nextGui()
{
  ++lib;
  if (lib == lLib.end())
    lib = lLib.begin();
}

void	Menu::prevGui()
{
  if (lib == lLib.begin())
    lib = lLib.end();
  --lib;
}

void		Menu::chooseName()
{
  bool		done = false;

  while (done == false) {
    t_Event	event = gui->eventHandler();

    if (event.keyType == EV_KDOWN)
      switch ( event.keyValue ) {
      case K_ENTER:
	done = true;
	break;
      case K_DEL:
	if (name.empty() == false) {
	  name.erase(--name.end());
	  displayName();
	}
	break;
      case K_OTHER:
	if (((event.charName >= 'a' && event.charName <= 'z')
	     || (event.charName >= 'A' && event.charName <= 'Z')
	     || (event.charName >= '0' && event.charName <= '9')
	     || (event.charName == ' ' || event.charName == '_'))
	    && (name.length() < 20)) {
	  name += event.charName;
	  displayName();
	}
      default:
	break;
      }
  }
}

void	Menu::chooseGame()
{
  bool	done = false;

  displayGames();
  while (done == false) {
    t_Event	event = gui->eventHandler();

    if (event.keyType == EV_KDOWN)
      switch ( event.keyValue ) {
      case K_ENTER:
	done = true;
	break;
      case K_UP:
	prevGame();
	displayGames();
	break;
      case K_DOWN:
	nextGame();
	displayGames();
	break;
      default:
	break;
      }
  }  
}

void	Menu::chooseGui()
{
  bool	done = false;

  displayGuis();
  while (done == false) {
    t_Event	event = gui->eventHandler();

    if (event.keyType == EV_KDOWN)
      switch ( event.keyValue ) {
      case K_ENTER:
	done = true;
	break;
      case K_UP:
	prevGui();
	displayGuis();
	break;
      case K_DOWN:
	nextGui();
	displayGuis();
	break;
      default:
	break;
      }
  }  
}

void							Menu::displayBackGround() const
{
  std::vector<Objext<IGame *> *>::const_iterator	itGame;
  std::vector<Objext<IGui *> *>::const_iterator		itGui;
  t_Rect						r;
  t_Text						t;

  r.frame.set(0, 0, 50, 6);
  r.borderColor.set(255, 255, 0, 0, IRED);
  r.color.set(255, 0, 0, 0, IBLACK);
  gui->drawRect(r);

  t.frame.set(2, 2, 5, 2);
  t.text = "Name:";
  gui->drawText(t);

  r.frame.set(50, 0, 25, 50);
  r.borderColor.set(255, 0, 255, 0, IGREEN);
  gui->drawRect(r);

  r.frame.set(0, 6, 25, 44);
  r.borderColor.set(255, 0, 0, 255, IBLUE);
  gui->drawRect(r);

  r.frame.set(25, 6, 25, 44);
  r.borderColor.set(255, 255, 255, 0, IYELLOW);
  gui->drawRect(r);

  t.frame.set(4, 8, 0, 2);
  for (itGame = lGame.begin(); itGame != lGame.end(); itGame++, t.frame.y += 3) {
    t.frame.w = (*itGame)->getObj()->getName().length();
    t.text = (*itGame)->getObj()->getName();
    gui->drawText(t);
  }

  t.frame.set(29, 8, 0, 2);
  for (itGui = lLib.begin(); itGui != lLib.end(); itGui++, t.frame.y += 3) {
    t.frame.w = (*itGui)->getObj()->getName().length();
    t.text = (*itGui)->getObj()->getName();
    gui->drawText(t);
  }
  gui->refreshWindow();
}

void	Menu::displayName() const
{
  t_Text	t;
  t_Rect	r;

  r.frame.set(7, 2, 20, 2);
  r.borderColor.set(255, 0, 0, 0, IBLACK);
  r.color.set(255, 0, 0, 0, IBLACK);
  gui->drawRect(r);
  t.frame.set(7, 2, name.length(), 2);
  t.text = name;
  gui->drawText(t);
  gui->refreshWindow();
}

void							Menu::displayGames() const
{
  std::vector<Objext<IGame *> *>::const_iterator	it;
  t_Rect						r;

  r.frame.set(2, 8, 1, 1);
  r.vBorderChar = '>';
  for (it = lGame.begin(); it != lGame.end(); it++, r.frame.y += 3) {
    if (*it == *game) {
      r.borderColor.set(255, 255, 255, 255, IWHITE);
      r.color.set(255, 255, 255, 255, IWHITE);
    } else {
      r.borderColor.set(255, 0, 0, 0, IBLACK);
      r.color.set(255, 0, 0, 0, IBLACK);
    }
    gui->drawRect(r);
  }
  gui->refreshWindow();
}

void						Menu::displayGuis() const
{
  std::vector<Objext<IGui *> *>::const_iterator	it;
  t_Rect					r;

  r.frame.set(27, 8, 1, 1);
  r.vBorderChar = '>';
  for (it = lLib.begin(); it != lLib.end(); it++, r.frame.y += 3) {
    if (*it == *lib) {
      r.borderColor.set(255, 255, 255, 255, IWHITE);
      r.color.set(255, 255, 255, 255, IWHITE);
    } else {
      r.borderColor.set(255, 0, 0, 0, IBLACK);
      r.color.set(255, 0, 0, 0, IBLACK);
    }
    gui->drawRect(r);
  }
  gui->refreshWindow();
}

template<typename T>
void		Menu::findLibs(std::vector<Objext<T> *> *list,
			       const char *path, const char *pattern)
{
  glob_t	gbuf;
  int		err;

  if ((err = glob(pattern, 0, NULL, &gbuf)) != 0)
    throw ErrGlob(path, err);
  for (unsigned int i = 0; i < gbuf.gl_pathc; i++) {
    Objext<T> *obj = new Objext<T>();
    obj->init(gbuf.gl_pathv[i]);
    list->push_back(obj);
  }
  globfree(&gbuf);
}

