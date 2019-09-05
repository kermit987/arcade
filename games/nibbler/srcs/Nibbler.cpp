/*
** Nibbler.cpp for Nibbler in /home/clementine/rendu/arcade
** 
** Made by Clementine
** Login   <clementine@clementine>
** 
** Started on  Sat Mar 19 04:32:17 2016 Clementine
** Last update Sun Apr  3 22:14:27 2016 Clementine
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include "Nibbler.hpp"


extern "C" {
  void		Play(void)
  {
    Nibbler	nibbler;

    nibbler.Play();
  }

  IGame	*createLib(void)
  {
    return new Nibbler();
  }
}

Nibbler::Nibbler()
{
  where = reinterpret_cast<struct arcade::WhereAmI *>(new char[sizeof(struct arcade::WhereAmI) + sizeof(struct arcade::Position)]);
  gMap = reinterpret_cast<struct arcade::GetMap *>(new char[sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * 17 * 25]);

  drawBackground();
  drawWall();
  drawSnake();
  drawApple();

  _direction = 0;
}

void Nibbler::initWall(int x, int y)
{
  t_Frame	pos;
  t_Img		wall;
  t_Color	color;

  color.set(255, 255, 0, 0, IRED);
  pos.set(x, y, 4, 1);
  wall.set(pos, "./img/murr.jpeg", color, "H");
  _wall.push_back(wall);
}

void Nibbler::drawWall()
{
  initWall(2, 5);
  initWall(10, 5);
  initWall(18, 5);
  initWall(2, 18);
  initWall(10, 18);
  initWall(18, 18);
  initWall(10, 11);
}

void Nibbler::drawBackground()
{
  t_Frame	pos;
  t_Color	color;

  color.set(255, 255, 0, 0, IRED);
  pos.set(0, 0, 25, 25);
  background.set(pos, "./img/fond.jpg", color, "*");
}

void Nibbler::initSnake(int x, int y)
{
  t_Frame	pos;
  t_Color	color;

  color.set(255, 51, 204, 0, IGREEN);
  pos.set(x, y, 1, 1);
  snakeImg.set(pos, "./img/snake.png", color, "o");
  _snake.push_back(pos);
}

void Nibbler::Create()
{
  t_Frame pos;
  t_Color color;

  switch (static_cast<int>(key.keyValue))
    {
    case static_cast<int>(K_RIGHT):
      pos.set(_snake.back().x - 1, _snake.back().y, 1, 1);
      break;
    case static_cast<int>(K_LEFT):
      pos.set(_snake.back().x + 1, _snake.back().y, 1, 1);
      break;
    case static_cast<int>(K_UP):
      pos.set(_snake.back().x, _snake.back().y - 1, 1, 1);
      break;
    case static_cast<int>(K_DOWN):
      pos.set(_snake.back().x, _snake.back().y + 1, 1, 1);
      break;
    }
  _snake.push_back(pos);
}

void Nibbler::drawSnake()
{
  initSnake(10, 9);
  initSnake(10, 9);
  initSnake(9, 9);
  initSnake(8, 9);
}

bool Nibbler::checkSnake(int x, int y)
{
  std::list<t_Frame>::iterator it = _snake.begin();

  while (it != _snake.end())
    {
      if (it != _snake.begin() && (*it).x == x && (*it).y == y)
	return true;
      ++it;
    }
  return false;
}

bool Nibbler::checkWall(int x, int y)
{
  int i;
  
  for (t_Img wall : _wall)
    {
      i = wall.frame.x;
      while (i < (wall.frame.x + _wall.front().frame.w))
	{
	  if (i == x && wall.frame.y == y)
	    return true;
	  i += _wall.front().frame.h;
	}
    }  
  return false;
}

bool Nibbler::checkBorder(int x, int y)
{
  return (x < 0 || x > 24 || y < 0 || y > 24);
}

void Nibbler::drawApple()
{
  t_Color	color;
  int		x;
  int		y;
  
  x = (rand() % 25);
  y = (rand() % 25);
  while (checkSnake(x, y) || checkWall(x, y))
    {
      x = (rand() % 25);
      y = (rand() % 25);
    }
  apple.frame.set(x, y, 1, 1);
  color.set(255, 255, 255, 0, IYELLOW);
  apple.set(apple.frame, "./img/Pomme.png", color, "Q");
}

bool Nibbler::checkApple(int x, int y)
{
  return (apple.frame.x == x && apple.frame.y == y);
}

int Nibbler::Direction(int x, int y)
{
  _snake.back().x = x;
  _snake.back().y = y;
  _snake.push_front(_snake.back());
  _snake.pop_back();
  
  if (checkApple(_snake.front().x, _snake.front().y))
    {
      Create();
      drawApple();
    }
  
  if (checkBorder(_snake.front().x, _snake.front().y) ||
      checkWall(_snake.front().x, _snake.front().y) ||
      checkSnake(_snake.front().x, _snake.front().y))
    return 0;
  return 2;
}

bool Nibbler::Restart(t_KeyValue *keyReturn)
{
  _lib->cleanWindow();

  drawBackground();
  drawWall();
  drawSnake();
  drawApple();
  
  Start(_lib, NULL, keyReturn);

  return true;
}

int Nibbler::move(t_KeyValue *keyReturn)
{
  int returnValue = 2;
  
  switch (static_cast<int>(key.keyValue))
    {
    case static_cast<int>(K_RIGHT):
      {
	if (_direction != 1)
	  {
	    _direction = 0;
	    if (Direction(_snake.front().x + 1, _snake.front().y) == 0)
	      returnValue = 0;
	  }
	else
	  {
	    key.keyValue = K_LEFT;
	    move(keyReturn);
	  }
	break;
      }
      
    case static_cast<int>(K_LEFT):
      {
	if (_direction != 0)
	  {
	    _direction = 1;
	    if (Direction(_snake.front().x - 1, _snake.front().y) == 0)
	      returnValue = 0;
	  }
	else
	  {
	    key.keyValue = K_RIGHT;
	    move(keyReturn);
	  }
	break;
      }
      
    case static_cast<int>(K_UP):
      {
	if (_direction != 3)
	  {
	    _direction = 2;
	    if (Direction(_snake.front().x, _snake.front().y - 1) == 0)
	      returnValue = 0;
	  }
	else
	  {
	    key.keyValue = K_DOWN;
	    move(keyReturn);
	  }
	break;
      }
      
    case static_cast<int>(K_DOWN):
      {
	if (_direction != 2)
	  {
	    _direction = 3;
	    if (Direction(_snake.front().x, _snake.front().y + 1) == 0)
	      returnValue = 0;
	  }
	else
	  {
	    key.keyValue = K_UP;
	    move(keyReturn);
	  }
	break;
      }
      
    case static_cast<int>(K_ESCAPE):
      *keyReturn = K_ESCAPE;
      returnValue = 0;
      break;
      
    case static_cast<int>(K_2):
      *keyReturn = K_2;
      returnValue = 1;
      break;
    case static_cast<int>(K_3):
      *keyReturn = K_3;
      returnValue = 1;
      break;
    case static_cast<int>(K_4):
      *keyReturn = K_4;
      returnValue = 1;
      break;
    case static_cast<int>(K_5):
      *keyReturn = K_5;
      returnValue = 1;
      break;

    case static_cast<int>(K_8):
      *keyReturn = K_8;
      Restart(keyReturn);
      break;
    case static_cast<int>(K_9):
      *keyReturn = K_9;
      returnValue = 1;
      break;
    }
  return returnValue;
}

void Nibbler::DisplayMap()
{
  t_Color color;
  
  _lib->drawImg(background);
  for (t_Img & wall : _wall)
    _lib->drawImg(wall);
  for (t_Frame & snake : _snake)
    {
      color.set(255, 51, 204, 0, IGREEN);
      snakeImg.set(snake, "./img/snake.png", color, "o");
      _lib->drawImg(snakeImg);
    }
   // _lib->drawImg(fruit);
  _lib->drawImg(apple);
}

bool Nibbler::Start(IGui *library, const std::string &, t_KeyValue *keyReturn)
{
  int moveReturn;
  
  srand(time(NULL));
  _lib = library;

  _lib->createWindow(0, NULL, 25, 25);
  while (true)
    {
      key = _lib->eventHandler();
      if ((moveReturn = move(keyReturn)) == 1)
	return true;
      else if (moveReturn == 0)
	return false;
      DisplayMap();
      _lib->refreshWindow();
    }
  return true;
}

const std::string &Nibbler::getName() const
{
  return _name;
}

const std::string &Nibbler::getFileScoreName() const
{
  return _fileScore;
}

/* ------------------------ */
/*                          */
/*      FOR KOALINETTE      */
/*                          */
/* ------------------------ */

void Nibbler::initGetMap()
{
  int i = 0;
  int x = 0;
  int y;
  int map[17][25] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };
  
  gMap->type = arcade::CommandType::GET_MAP;
  gMap->width = 25;
  gMap->height = 17;
  while (map[x])
    {
      y = 0;
      while (map[x][y])
	{
	  gMap->tile[i] = static_cast<arcade::TileType>(map[x][y]);
	  ++y;
	  ++i;
	}
      ++x;
    }
}

void Nibbler::initWhereAmI()
{
  where->type = arcade::CommandType::WHERE_AM_I;
  where->lenght = 1;
  where->position[0].x = 11;
  where->position[0].y = 7;
}

void Nibbler::DirectionMap(uint16_t a, uint16_t b, int i)
{
  int x;
  int y = 0;
  
  x = where->position[0].x * 25 + where->position[0].y;
  if (gMap->tile[x + i] != arcade::TileType::BLOCK)
    {
      while (y < where->lenght)
	++y;
      while (y > 0)
	{
	  where->position[y] = where->position[y - 1];
	  --y;
	}
      where->position[y].x = a;
      where->position[y].y = b;
    }
}

void Nibbler::checkPlayCommand(const char &command)
{
  int com = command;

  switch (com)
    {
    case 0:
      std::cout.write(reinterpret_cast<char *>(where), sizeof(struct arcade::WhereAmI) + sizeof(struct arcade::Position));
      break;
    case 1:
      std::cout.write(reinterpret_cast<char *>(gMap), sizeof(struct arcade::GetMap) + sizeof(arcade::TileType) * 17 * 25);
      break;
    case 2:
      DirectionMap(where->position[0].x, where->position[0].y - 1, -25);
      _command = '\02';
      break;
    case 3:
      DirectionMap(where->position[0].x, where->position[0].y + 1, 25);
      _command = '\03';
      break;
    case 4:
      DirectionMap(where->position[0].x - 1, where->position[0].y, -1);
      _command = '\04';
      break;
    case 5:
      DirectionMap(where->position[0].x + 1, where->position[0].y, 1);
      _command = '\05';
      break;
    case 6:
      checkPlayCommand(_command);
      break;
    case 8:
      break;
    case 9:
      break;
    }
}

void Nibbler::Play(void)
{
  char command[2] = "";

  initGetMap();
  initWhereAmI();
  while (true)
    {
      std::cin.get(command, 2);
      checkPlayCommand(command[0]);
    }
}
