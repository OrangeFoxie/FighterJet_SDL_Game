
#include "BaseObject.h"

BaseObject::BaseObject()	// Dinh nghia ham tao BaseObject
{
  rect_.x = 0;	// toa do truc X
  rect_.y = 0;	// toa do truc Y
  p_object_ = NULL;	// khoi tao vat the tai vi tri x,y
}

BaseObject::~BaseObject()	// Dinh nghia ham xoa obj
{
  if (p_object_ != NULL)	// Kiem tra dieu kien
  {
    SDL_FreeSurface(p_object_);	// Xoa vat the
  }
}

bool BaseObject::LoadImg(const char* file_name)	// Kiem tra va load images
{
  p_object_ = SDLCommonFunc::LoadImage(file_name); // Goi ham load images
  if (p_object_ == NULL)	// ko co anh thi load
    return false;	
  return true;	// co roi thi khong load
}

void BaseObject::Show(SDL_Surface* des)
{
  if (p_object_ != NULL)	// load duoc anh roi thi show len man hinh
  {
    SDLCommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y);
  }
}
