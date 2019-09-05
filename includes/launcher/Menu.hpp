//
// Menu.hpp for  in /home/metz_a/rendu/cpp_arcade
// 
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
// 
// Started on  Fri Mar 18 16:45:46 2016 Aurélien METZ Aurélien
// Last update Thu Mar 31 15:02:54 2016 Aurélien METZ Aurélien
//

#ifndef MENU_HPP_
# define MENU_HPP_

# include "IGame.hpp"
# include "IGui.hpp"
# include "Objext.hpp"
# include <vector>
# include <string>

class	Menu
{
public:
  Menu();
  ~Menu();
  void							start(IGui *);
  const std::string&					getName() const;
  const std::vector<Objext<IGame *> *>::iterator&	getGame() const;
  const std::vector<Objext<IGui *> *>::iterator&	getLib() const;
  void							nextGame();
  void							prevGame();
  void							nextGui();
  void							prevGui();
private:
  void							chooseName();
  void							chooseGame();
  void							chooseGui();
  void							displayBackGround() const;
  void							displayName() const;
  void							displayGames() const;
  void							displayGuis() const;
  template<typename T>
  void						findLibs(std::vector<Objext<T> *> *,
							 const char *, const char *);

  IGui						*gui;
  std::string					name;
  std::vector<Objext<IGame *> *>		lGame;
  std::vector<Objext<IGame *> *>::iterator	game;
  std::vector<Objext<IGui *> *>			lLib;
  std::vector<Objext<IGui *> *>::iterator	lib;
};

#endif /* !MENU_HPP_ */
