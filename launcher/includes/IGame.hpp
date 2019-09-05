//
// IGame.hpp for  in /home/metz_a/rendu/cpp_arcade
//
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
//
// Started on  Thu Mar 10 13:27:24 2016 Aurélien METZ Aurélien
// Last update Tue Mar 15 12:12:43 2016 Steven Loo Fat
//

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include "IGui.hpp"

class	IGame
{
public:
  IGame(void) {}
  virtual ~Igame(void) {}
  virtual void	Play(void) = 0;
  virtual bool	start(IGui *) = 0; // pour la moulinette
  virtual bool	end(void) = 0;
};

#endif /* !IGAME_HPP_ */
