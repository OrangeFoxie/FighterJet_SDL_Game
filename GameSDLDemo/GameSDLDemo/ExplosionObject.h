
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "BaseObject.h"
#include "Common_Function.h"

const int EXP_WIDTH = 165; // chieu ngang cua explosion
const int EXP_HEIGHT = 165; // chieu doc cua explosion

class ExplosionObject : public BaseObject
{
public:
  ExplosionObject(); //tao ham explosion
  ~ExplosionObject(); // thoat ham explosion
  void set_clip();	//load img explosion
  void set_frame(const int& fr) {frame_ = fr;} // time dien ra explosion
  void ShowEx(SDL_Surface* des); // hien thi explosion len man hinh

private:
  int frame_;
  SDL_Rect clip_[4];
};

#endif