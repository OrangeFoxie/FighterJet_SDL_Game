
#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
	// khoi tao ham explosion
}

ExplosionObject::~ExplosionObject()
{// ket thuc ham

}

void ExplosionObject::set_clip()
{
  clip_[0].x = 0; //  vi tri x
  clip_[0].y = 0; //  vi tri x
  clip_[0].w = EXP_WIDTH; // dai
  clip_[0].h = EXP_HEIGHT;// rong

  clip_[1].x = EXP_WIDTH;
  clip_[1].y = 0;
  clip_[1].w = EXP_WIDTH;
  clip_[1].h = EXP_HEIGHT;

  clip_[2].x = 2*EXP_WIDTH;
  clip_[2].y = 0;
  clip_[2].w = EXP_WIDTH;
  clip_[2].h = EXP_HEIGHT;

  clip_[3].x = 3*EXP_WIDTH;
  clip_[3].y = 0;
  clip_[3].w = EXP_WIDTH;
  clip_[3].h = EXP_HEIGHT;
}

void ExplosionObject::ShowEx(SDL_Surface* des)
{// hien thi hieu ung explosion trong frame
  if (frame_ >= 4)
  {
    frame_ = 0;
  }

  SDLCommonFunc::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}