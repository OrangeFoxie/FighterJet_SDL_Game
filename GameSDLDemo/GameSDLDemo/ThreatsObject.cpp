
#include "ThreatsObject.h"

ThreatObject::ThreatObject() // khoi tao 1 enemy
{
  rect_.x = SCREEN_WIDTH; // vi tri x cua enemy
  rect_.y = SCREEN_HEIGHT*0.5; // vi tri y cua enemy, *0.5 de luc khi dc sinh ra thi cac enemy ko nam trung len nhau
  rect_.w = WIDTH_THREAT; // chieu ngang
  rect_.h = HEIGHT_THREAT;// chieu cao

  x_val_ = 0; // di chuyen x cua enemy
  y_val_ = 0; // di chuyen y cua enemy
}

ThreatObject::~ThreatObject()
{
  if (p_bullet_list_.size() > 0) //kiem tra xem co ammo nao dang bay trong game k
  {
    for (int i = 0; i < p_bullet_list_.size(); i++) // lap danh sach ammo dang ton tai
    {
      BulletObject* p_bullet = p_bullet_list_.at(i);
      if (p_bullet != NULL) // Kiem tra xem con vien dan nao trong list
      {
        delete p_bullet; // disble vien dan neu enemy die
        p_bullet = NULL;
      }
    }
    p_bullet_list_.clear(); // xoa ammo khoi man hinh
  }
}


void ThreatObject::InitBullet(BulletObject* p_bullet)
{// tao ra 1 ammo cua enemy
  if (p_bullet)
  {
    bool ret = p_bullet->LoadImg(g_name_bullet_threats); // ktra viec load img cua ammo
    if (ret)
    {
      p_bullet->set_is_move(true);// ammo dang bay
      p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE); // set chieu height, width cho ammo
      p_bullet->set_type(BulletObject::SPHERE); // type cua ammo
      p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);// vung va cham cua ammo
      p_bullet->set_x_val(SPEED_BULLET_THREATS);// toc do cua ammo
      p_bullet_list_.push_back(p_bullet); // dua ammo roi nong sung cua enemy, ban auto
    }
  }
}


void ThreatObject::MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit)
{// tao 1 ammo
  for (int i = 0; i < p_bullet_list_.size(); i++) // tao 1 danh sach ammo
  {
    BulletObject* p_bullet = p_bullet_list_.at(i); // ammo tai vi tri i trong list
    if (p_bullet)
    {
      if (p_bullet->get_is_move()) // ktra ammo co dang di chuyen
      {
        p_bullet->Show(des);// hien thi ammo
        p_bullet->HandleMoveRightToLeft(); // ammo bay tu trai sang phai
      }
      else
      {// ko co ammo thi tao 1 ammo roi set vung va cham cho no
        p_bullet->set_is_move(true); 
        p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
      }
    }
  }
}

void ThreatObject::HandleMove(const int& x_bordr, const int& y_border)
{// ham di chuyen cua enemy
  rect_.x -= x_val_;
  if (rect_.x < 0)// di chuyen tu right to left
  {
    rect_.x  = SCREEN_WIDTH;
    rect_.y= SDLCommonFunc::MakeRandValue();
  }
}

void ThreatObject::HandleInputAction(SDL_Event events)
{
  //Todo
}


void ThreatObject::Reset(const int& xboder)
{// ham auto ban cua enemy
  rect_.x = xboder; 
  rect_.y = SDLCommonFunc::MakeRandValue();

  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    BulletObject* p_bullet = p_bullet_list_.at(i);
    if (p_bullet)
    {
      ResetBullet(p_bullet);
    }
  }
}

void ThreatObject::ResetBullet(BulletObject* p_bullet)
{// update moi ammo khi no dang bay
   p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
}