
#include "BulletObject.h"

BulletObject::BulletObject()
{
  rect_.x = 0; // vi tri X cua ammo
  rect_.y = 0;	// vi tri Y cua ammo	
  x_val_ = 0;	// vi tri X update cua ammo
  y_val_ = 0;	// vi tri Y update cua ammo
  is_move_ = false; // ammo chua ra khoi gun thi nam trong gun
  bullet_type_ = NONE;	// waiting for player to select the type of ammo by clicking their mouse's button
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{ // update duong di cua dang
  if (is_move_ == true)
  {
    rect_.x += x_val_; // dang move tinh tien ve phia truoc
    if (rect_.x > x_border)
    {
      is_move_ = false; // ammo di den goc phai cua window thi bien mat
    }
  }
}

void BulletObject::HandleMoveRightToLeft()
{ // ammo cua enemy bay tu phai sang trai
  rect_.x -= x_val_; 
  if (rect_.x < 0) // ammo di den goc trai cua window thi bien mat
  {
    is_move_ = false;
  }
}

void BulletObject::HandleInputAction(SDL_Event events)
{
  //Todo
}
