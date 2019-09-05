//
// pacman.cpp for  in /home/steven/generique_pacman
//
// Made by Steven Loo Fat
// Login   <loofat_s@epitech.net>
//
// Started on  Sat Apr  2 11:48:28 2016 Steven Loo Fat
// Last update Sun Apr  3 17:47:23 2016 Steven Loo Fat
//

#include <string>
#include <iostream>
#include <vector>
#include "IGame.hpp"
#include "Pacman.hpp"
#include "Protocol.hpp"
#include "ErrorManagment.hpp"

extern "C"
{
  void		Play(void)
  {
    Pacman	pacman;

    pacman.Play();
  }

  IGame	 *createLib(void)
  {
    return new Pacman();
  }
}

Pacman::Pacman(): name("Pacman"), fileScoreName("ScorePacman")
{
  int   x;
  int   y;
  int	map[20][20]= {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };

  whereami = reinterpret_cast<arcade::WhereAmI*>(new char (sizeof(arcade::WhereAmI) + sizeof(arcade::Position) * (1)));
  whereami->type = this->commande_type;
  whereami->lenght = 1;
  getmap = reinterpret_cast<arcade::GetMap*>(new char (sizeof(arcade::GetMap) + sizeof(arcade::TileType) * (20 * 20)));
  getmap->type = arcade::CommandType::GET_MAP;
  getmap->width = 20;
  getmap->height = 20;
  for (x = 0; x < 20; x++)
    for (y = 0; y < 20; y++)
      if (map[x][y] == 1)
	getmap->tile[(x * 20) + y] = static_cast<arcade::TileType>(arcade::TileType::OBSTACLE);
      else
	getmap->tile[(x * 20) + y] = static_cast<arcade::TileType>(arcade::TileType::POWERUP);
  this->getmap->tile[this->whereami->position[0].x + (this->whereami->position[0].y - 1) * 20] = arcade::TileType::EMPTY;
  direction = arcade::CommandType::GO_LEFT;
}

Pacman::~Pacman()
{
  delete whereami;
  delete getmap;
}

const std::string&	Pacman::getName() const
{
  return (name);
}

const std::string&	Pacman::getFileScoreName() const
{
  return (fileScoreName);
}

void		        Pacman::add_getmap()
{
  std::cout.write(reinterpret_cast<char *>(this->getmap), sizeof(arcade::GetMap) + sizeof(arcade::TileType) * (20 * 20));
}

void			Pacman::add_position()
{
  switch ( commande_type )
    {
    case arcade::CommandType::GO_FORWARD:
      commande_type = direction;
    case arcade::CommandType::GO_UP:
      direction = arcade::CommandType::GO_UP;
      if (this->getmap->tile[this->whereami->position[0].x + (this->whereami->position[0].y - 1) * 20] != arcade::TileType::OBSTACLE)
	this->whereami->position[0].y--;
      break;
    case arcade::CommandType::GO_DOWN:
      direction = arcade::CommandType::GO_DOWN;
      if (this->getmap->tile[this->whereami->position[0].x + (this->whereami->position[0].y + 1) * 20] != arcade::TileType::OBSTACLE)
	this->whereami->position[0].y++;
      break;
    case arcade::CommandType::GO_LEFT:
      direction = arcade::CommandType::GO_LEFT;
      if (this->getmap->tile[this->whereami->position[0].x - 1 + this->whereami->position[0].y * 20] != arcade::TileType::OBSTACLE)
	this->whereami->position[0].x--;
      break;
    case arcade::CommandType::GO_RIGHT:
      direction = arcade::CommandType::GO_RIGHT;
      if(this->getmap->tile[this->whereami->position[0].x + 1 + this->whereami->position[0].y * 20] == arcade::TileType::OBSTACLE)
	this->whereami->position[0].x++;
    default:
      break;
    }
  if (this->getmap->tile[this->whereami->position[0].x + (this->whereami->position[0].y - 1) * 20] == arcade::TileType::POWERUP)
    this->getmap->tile[this->whereami->position[0].x + (this->whereami->position[0].y - 1) * 20] = arcade::TileType::EMPTY;
}

void			Pacman::add_whereami()
{
  std::cout.write(reinterpret_cast<char *>(this->whereami), sizeof(arcade::WhereAmI) + sizeof(arcade::Position) * (1));
}

void			Pacman::Play()
{
  int					i;
  char					user_input[2];
  arcade::CommandType			tab[10];
  void(Pacman::*tab_function[7])(void);

  //
  tab[0] = arcade::CommandType::WHERE_AM_I;
  tab[1] = arcade::CommandType::GET_MAP;
  tab[2] = arcade::CommandType::GO_UP;
  tab[3] = arcade::CommandType::GO_DOWN;
  tab[4] = arcade::CommandType::GO_LEFT;
  tab[5] = arcade::CommandType::GO_RIGHT;
  tab[6] = arcade::CommandType::GO_FORWARD;
  // tab[7] = arcade::CommandType::SHOOT;
  // tab[8] = arcade::CommandType::ILLEGAL;
  // tab[9] = arcade::CommandType::PLAY;
  //
  tab_function[0] = &Pacman::add_whereami;
  tab_function[1] = &Pacman::add_getmap;
  tab_function[2] = &Pacman::add_position;
  tab_function[3] = &Pacman::add_position;
  tab_function[4] = &Pacman::add_position;
  tab_function[5] = &Pacman::add_position;
  tab_function[6] = &Pacman::add_position;
  //
  while (true)
    {
      std::cin.get(user_input, 2);
      i = 0;
      while (i != 7)
	{
	  if (i == static_cast<int>(user_input[0]))
	    {
	      this->commande_type = tab[i];
	      (this->*tab_function[i])();
	      break ;
	    }
	  i++;
	}
    }
}

void	Pacman::display_map()
{
  t_Rect	rect;
  int   x;
  int   y;

  x = 0;
  y = 0;
  while (x != 1000)
    {
      y = 0;
      while (y != 1000)
	{
	  // rect.frame.set(x * 50, y * 50, (x * 50) + 50, (y * 50) + 50);
	  rect.frame.set(x, y, x + 1, y + 1);
	  // rect.frame.set(x, y, x, y);
	  if (this->getmap->tile[(x / 50) + (y / 50) * 20] == arcade::TileType::OBSTACLE)
	    {
	      rect.color.set(0,0,0,255,IWHITE);
	    }
	  else
	    {
	      rect.color.set(0,0,0,0,IWHITE);
	    }
	  y++;
	}
      x++;
    }
}

bool			Pacman::Start(IGui *igui, const std::string &, t_KeyValue *key)
{
  bool			done;
  t_Text		text;
  t_Event		event;
  t_Img			pacman;

  try {
    igui->createWindow(0, 0, 20, 20);
    text.frame.set(10, 10, 0, 0);
    text.color.set(0, 255, 255, 0, IRED);
    text.text = "Pacman";
    igui->drawText(text);
    igui->refreshWindow();
    igui->eventHandler();
    this->display_map();
    done = true;
    while (done)
      {
	event = igui->eventHandler();
	*key = event.keyValue;
	if (event.keyType == EV_KDOWN)
	  switch (event.keyValue) {
	  case K_ESCAPE:
	    done = false;
	    break;
	  case K_2:
	  case K_3:
	  case K_4:
	  case K_5:
	    return (false);
	  case K_8:
	    //this->restart(); créer une methode restart pour remettre le jeux à zero
	    break;
	  case K_9:
	    return (true);
	  case K_UP:
	    break;
	  case K_DOWN:
	    break;
	  case K_LEFT:
	    break;
	  case K_RIGHT:
	    break;
	  default:
	    break;
	  }
	pacman.frame.set(whereami->position[0].x, whereami->position[0].y, 1, 1);
	pacman.color.set(255, 255, 255, 0, IYELLOW);
	pacman.set(pacman.frame, "image_pacman", pacman.color, "@");
	if (igui->drawImg(pacman) == false)
	  throw ErrFile("image_pacman");
      }
    igui->refreshWindow();
  }
  catch (std::exception &e)
    {
      std::cout << e.what() << std::endl;
      return (true);
    }
  return (true);
}

bool			Pacman::End()
{
  return (true);
}
