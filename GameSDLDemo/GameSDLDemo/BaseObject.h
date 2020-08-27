
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public:
  BaseObject();	// Tao ham Baseobj
  ~BaseObject();// Thoat ham BaseObj
  void Show(SDL_Surface* des);	// Ve mat dat cua game
  bool LoadImg(const char* file_name);	// Kiem tra viec load background va hinh anh player

  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}	// Tao vung chua hinh anh
  SDL_Rect GetRect() const {return rect_;}		// Gan hinh anh cho moi vat the
  SDL_Surface* GetObject() {return p_object_;}	// tao be mat dat trong game
protected:										
  SDL_Rect rect_;			// tao bien tinh, khong thay doi theo time
  SDL_Surface* p_object_;	
};

#endif 