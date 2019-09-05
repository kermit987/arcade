/*
** Data.hpp for  in /home/clementine/rendu/arcade
**
** Made by Clementine
** Login   <clementine@epitech.net>
**
** Started on  Wed Mar 23 12:28:06 2016 Clementine
// Last update Sun Apr  3 11:20:47 2016 Aurélien METZ Aurélien
*/

#ifndef DATA_HPP_
# define DATA_HPP_

# include <string>

enum enumColor {
    IRED = 1,
    IGREEN,
    IYELLOW,
    IBLUE,
    IMAGENTA,
    ICYAN,
    IWHITE,
    IBLACK
};

struct	t_Color
{
  unsigned char	a;
  unsigned char	r;
  unsigned char	g;
  unsigned char	b;
  enumColor	colorNc;

  t_Color(void): a(255), r(255), g(255), b(255), colorNc(IWHITE) {}
  void set(int _a, int _r, int _g, int _b, enumColor ncolor) {
    a = _a;
    r = _r;
    g = _g;
    b = _b;
    colorNc = ncolor;
  }
};

struct	t_Frame
{
  int		x;
  int		y;
  int		w;
  int		h;

  t_Frame(void): x(0), y(0), w(0), h(0) {}
  void set(int _x, int _y, int _w, int _h) {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
  }
};

struct	t_Rect
{
  t_Frame	frame;
  t_Color	color;
  t_Color	borderColor;
  int		borderWidth;
  char		vBorderChar; //Terminal use only
  char		hBorderChar; //Terminal use only

  t_Rect(void): borderWidth(1), vBorderChar('|'), hBorderChar('*') {}
  void set(t_Frame _frame, t_Color _color, t_Color _borderColor, int _borderWidth, char _vBorderChar, char _hBorderChar) {
    frame = _frame;
    color = _color;
    borderColor = _borderColor;
    borderWidth = _borderWidth;
    vBorderChar = _vBorderChar;
    hBorderChar = _hBorderChar;
  }
};

struct	t_Text
{
  t_Frame	frame;
  t_Color	color;
  std::string	text;

  t_Text(void) {}
  void set(t_Frame _frame, t_Color _color, std::string _text) {
    frame = _frame;
    color = _color;
    text = _text;
  }
};

struct	t_Img
{
  t_Frame	frame;
  std::string	filename;
  t_Color	color;
  std::string	ncImg;

  t_Img(void) {}
  void set(t_Frame _frame, std::string _filename, t_Color _color, std::string _ncImg)
  {
    frame = _frame;
    filename = _filename;
    color = _color;
    ncImg = _ncImg;
  }
};

enum t_EventType
  {
    EV_NOTHING,
    EV_KDOWN,
    EV_RESIZE,
    EV_KUP
  };

enum t_KeyValue
  {
    K_ESCAPE = 0,
    K_ENTER,
    K_DEL,
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_2,
    K_3,
    K_4,
    K_5,
    K_8,
    K_9,
    K_OTHER
  };

struct	t_Event
{
public:
  t_EventType	keyType;
  t_KeyValue	keyValue;
  char		charName;

  t_Event(void): keyType(EV_NOTHING), keyValue(K_OTHER), charName(0) {}
  void	set(t_EventType kt, t_KeyValue kv, char cn) {
    keyType = kt;
    keyValue = kv;
    charName = cn;
  }
};

struct	t_Score {
  std::string	name;
  std::string	pts;
};

#endif /* !DATA_HPP_ */
