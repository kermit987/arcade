//
// main.cpp for  in /home/metz_a/rendu/cpp_arcade/launcher/srcs
// 
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
// 
// Started on  Tue Mar 15 16:51:37 2016 Aurélien METZ Aurélien
// Last update Sat Apr  2 19:43:29 2016 Aurélien METZ Aurélien
//

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Menu.hpp"
#include "IGame.hpp"
#include "IGui.hpp"
#include "Objext.hpp"
#include "ErrorManagment.hpp"

int						main(int ac, char **av)
{
  Menu						menu;
  Objext<IGui *>				libLauncher;
  t_KeyValue					exit_status = K_OTHER;

  try {
    if (ErrorManagment::usage(ac, av) == false)
      throw ErrUsage();
    if (ErrorManagment::exist(av[1]) == false)
      throw ErrFile(av[1]);
    libLauncher.init(av[1]);
    menu.start(libLauncher.getObj());
    while (exit_status != K_ESCAPE) {
      if ((*menu.getGame())->getObj()->Start((*menu.getLib())->getObj(),
					     menu.getName(), &exit_status))
	break;
      (*menu.getLib())->getObj()->destroyWindow();
      switch ( exit_status ) {
      case K_2:
	menu.prevGui();
	break;
      case K_3:
	menu.nextGui();
	break;
      case K_4:
	menu.prevGame();
	break;
      case K_5:
	menu.nextGame();
	break;
      case K_9:
	menu.start(libLauncher.getObj());
	break;
      default:
	return EXIT_SUCCESS;
      }
    }
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
