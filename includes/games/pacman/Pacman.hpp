//
// Pacman.hpp for  in /home/steven/generique_pacman
//
// Made by Steven Loo Fat
// Login   <loofat_s@epitech.net>
//
// Started on  Wed Mar 30 18:45:10 2016 Steven Loo Fat
// Last update Sun Apr  3 17:45:40 2016 Steven Loo Fat
//

#ifndef PACMAN_HPP_
# define PACMAN_HPP_

#include <vector>
#include "Protocol.hpp"
#include "IGame.hpp"

class	Pacman: public IGame
{
public:
  Pacman();
  ~Pacman();
public:
  virtual const std::string&	getName() const;
  virtual const std::string&	getFileScoreName() const;
  virtual void			Play();
  virtual bool			Start(IGui *, const std::string &, t_KeyValue *);
  virtual bool			End();
  //
  void				add_getmap();
  void				add_position();
  void				add_whereami();
  // fonction pour le jeux
  void				display_map();
private:
  std::string			name;
  std::string			fileScoreName;
  struct arcade::WhereAmI	*whereami;
  struct arcade::GetMap		*getmap;
  arcade::CommandType		commande_type;
  arcade::CommandType		direction;
};
#endif	// !PACMAN_HPP_
