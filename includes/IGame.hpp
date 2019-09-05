/*
** IGame.hpp for  in /home/clementine/rendu/arcade
** 
** Made by Clementine
** Login   <clementine@epitech.net>
** 
** Started on  Fri Apr  1 19:29:01 2016 Clementine
** Last update Sun Apr  3 22:30:02 2016 Clementine
*/

#ifndef IGAME_HPP_
# define IGAME_HPP_

# include <string>
# include "IGui.hpp"

class	IGame
{
public:
  IGame(void) {}
  virtual ~IGame(void) {}

  virtual const std::string&	getName() const = 0;
  virtual const std::string&	getFileScoreName() const = 0;
  virtual void	Play() = 0;
  virtual bool	Start(IGui *, const std::string &, t_KeyValue *) = 0;
};

typedef IGame	*(*t_GameCreator)(void);

#endif /* !IGAME_HPP_ */
