//
// ErrorManagment.hpp for  in /home/metz_a/rendu/cpp_arcade/includes
//
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
//
// Started on  Tue Mar 15 15:05:40 2016 Aurélien METZ Aurélien
// Last update Sat Apr  2 23:11:33 2016 Aurélien METZ Aurélien
//

#ifndef ERRORMANAGMENT_HPP_
# define ERRORMANAGMENT_HPP_

# include <exception>
# include <iostream>
# include <fstream>
# include <string>
# include <glob.h>

class	ErrUsage : public std::exception
{
  virtual const char *what() const throw()
  { return "\nUsage :\n\n\t./arcade ./lib/lib_arcade_[...].so\n"; }
};

class	ErrFile : public std::exception
{
public:
  ErrFile(const char *filename): msg(filename) { msg += ": no such file"; }
  virtual ~ErrFile() throw() {}
  virtual const char	*what() const throw() { return msg.c_str(); }
private:
  std::string	msg;
};

class	ErrDl : public std::exception
{
public:
  ErrDl(const char *_msg): msg(_msg) {}
  virtual ~ErrDl() throw() {}
  virtual const char	*what() const throw() { return msg.c_str(); }
private:
  std::string		msg;
};

class	ErrGlob : public std::exception
{
public:
  ErrGlob(const char *path, int errcode) { buildMsg(path, errcode); }
  virtual ~ErrGlob() throw() {}
  virtual const char	*what() const throw() { return msg.c_str(); }
private:
  std::string		msg;
  void			buildMsg(const char *path, int errcode)
  {
    switch ( errcode ) {
    case GLOB_ABORTED:
      msg = "glob: aborted";
      break;
    case GLOB_NOMATCH:
      msg = "No valid library have been found in \'";
      msg += path;
      msg += "\'";
      break;
    case GLOB_NOSPACE:
      msg = "glob: An attempt to allocate memory failed";
    default:
      break;
    }
  }
};

class	ErrGui : public std::exception
{
public:
  ErrGui(const std::string &lib, const char *_msg) { buildMsg(lib, _msg); }
  virtual ~ErrGui() throw() {}
  virtual const char	*what() const throw() { return msg.c_str(); }
private:
  std::string	msg;
  void		buildMsg(const std::string &lib, const char *_msg)
  {
    msg = lib;
    msg += ": ";
    msg += _msg;
  }
};

class	ErrorManagment
{
public:
  static bool	usage(int ac, char **av) { return ac == 2 && av[1]; }
  static bool	exist(const char *filename)
  {
    std::ifstream	ifile(filename);

    if (ifile.is_open() == false)
      return false;
    ifile.close();
    return true;
  }
};

#endif /* !ERRORMANAGMENT_HPP_ */
