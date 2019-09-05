//
// Creator.hpp for  in /home/metz_a/rendu/cpp_arcade/launcher
// 
// Made by Aurélien METZ Aurélien
// Login   <metz_a@epitech.net>
// 
// Started on  Tue Mar 15 17:18:59 2016 Aurélien METZ Aurélien
// Last update Mon Mar 21 18:17:33 2016 Aurélien METZ Aurélien
//

#ifndef CREATOR_HPP_
# define CREATOR_HPP_

# include <string>
# include <dlfcn.h>
# include "ErrorManagment.hpp"

template<typename T>
class	Objext
{
public:
  Objext(): obj(NULL), handle(NULL) {}
  ~Objext()
  {
    if (obj)
      delete obj;
    if (handle)
      dlclose(handle);
  }
  void		init(const char *filename)
  {
    char	*error;
    T		(*creator)();

    if ((handle = dlopen(filename, RTLD_LAZY)) == NULL)
      throw ErrDl(dlerror());
    creator = reinterpret_cast<T (*)()>(dlsym(handle, "createLib"));
    if ((error = dlerror()))
      throw ErrDl(error);
    obj = creator();
  }
  T	getObj(void) const { return obj; }
  void	setObj(T o) { obj = o; }
private:
  T	obj;
  void	*handle;
};

#endif /* !CREATOR_HPP_ */
