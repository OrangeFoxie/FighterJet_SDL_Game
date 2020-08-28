
#include "MainObject.h"

MainObject::MainObject()
{
  rect_.x = 0; // vi tri x cua player
  rect_.y = 0; // vi tri y cua player
  rect_.w = WIDTH_MAIN_OBJECT; // chieu ngang cua player
  rect_.h = HEIGHT_MAIN_OBJECT; // chieu cao cua player
  x_val_ = 0;	// chi so di chuyen cua player theo chieu ngang
  y_val_ = 0;	// chi so di chuyen cua player theo chieu doc
}

MainObject::~MainObject()
{

}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2])
{
  if (events.type == SDL_KEYDOWN)
  {
    switch (events.key.keysym.sym) // nhan thong tin tu phim mui ten
    {
    case SDLK_UP: // bay len neu bam phim mui ten len
      y_val_ -= SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_DOWN: // bay xuong neu bam phim mui ten xuong
      y_val_ += SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_RIGHT: // di chuyen ra truoc neu bam phim mui ten phai
      x_val_ += SPEED_MAIN_OBJECT;
      //Todo
      break;
    case SDLK_LEFT: // di chuyen ra sau neu bam phim mui ten trai
      x_val_ -= SPEED_MAIN_OBJECT;
      break;;
    default:
      break;
    }
  }
  else if (events.type == SDL_KEYUP) // khong co ham nay thi 1 lan bam phim no move luon va khong dung lai
  {
    switch(events.key.keysym.sym )
    {
      case SDLK_UP: y_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_DOWN: y_val_ -= SPEED_MAIN_OBJECT; break;
      case SDLK_LEFT: x_val_ += SPEED_MAIN_OBJECT; break;
      case SDLK_RIGHT: x_val_ -= SPEED_MAIN_OBJECT; break;
    }
  }
  else if (events.type == SDL_MOUSEBUTTONDOWN) // lang nghe su lien tu mouse click
  {
    BulletObject* p_bullet = new BulletObject(); // tao 1 ammo khi click
    if (events.button.button == SDL_BUTTON_LEFT) // chuot trai dc click
    {
      p_bullet->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER); // tao ra ammo laser khi click chuot trai
      p_bullet->LoadImg(g_name_bullet_main_laser);	// load img cua laser
      p_bullet->set_type(BulletObject::LASER);	// gan type laser cho ammo
      Mix_PlayChannel(-1, bullet_sound[0], 0); // sound cua ammo
    }
    else if (events.button.button == SDL_BUTTON_RIGHT) // tao ra phi tieu khi click chuot phai
    {
      p_bullet->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE); // tao ra ammo khi click chuot vs chieu cao, chieu dai cua ammo
      p_bullet->LoadImg(g_name_bullet_main_fire); // load img cua ammo
      p_bullet->set_type(BulletObject::SPHERE);	// gan tyoe cho ammo
      Mix_PlayChannel(-1, bullet_sound[1], 0); // sound cua ammo
    }

    p_bullet->SetRect(this->rect_.x + this->rect_.w - 40, this->rect_.y + this->rect_.h*0.8); // vung pixel cua ammo, neu enemy hay player nam trong vung nay thi ho bi trung dan va die
    p_bullet->set_is_move(true); // ammo can moving
    p_bullet->set_x_val(SPEED_BULLET_MAIN); // speed of ammo
    p_bullet_list_.push_back(p_bullet); // danh sach cua ammo
  }
  else if (events.type == SDL_MOUSEBUTTONUP)
  {

  }
  else
  {
    //;
  }
}

void MainObject::MakeBullet(SDL_Surface* des) // tao 1 ammo
{
  for (int i = 0; i < p_bullet_list_.size(); i++) // tao 1 list ammo khi fire
  {
    BulletObject* p_bullet_ = p_bullet_list_.at(i); // so luong ammo sau khi ban ra cua 1 obj
    if (p_bullet_ != NULL) // co ammo dc ban ra
    {
      if (p_bullet_->get_is_move()) // kiem tra xem ammo co dang nam trong vung di chuyen k ?
      {
        p_bullet_->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT); // co thi cho ammo move
        p_bullet_->Show(des); // hien thi ammo
      }
      else 
      {
        if (p_bullet_ != NULL)
        {
          p_bullet_list_.erase(p_bullet_list_.begin() + i); // neu ammo trung ai, hoac ra khoi window thi...
          delete p_bullet_; // ammo bi delete
          p_bullet_ = NULL; // ammo do da bi disable
        }
      }
    }
  }
}



//************************************
// Method:    HandleMove
// FullName:  MainObject::HandleMove
// Access:    public 
// Returns:   void
// Qualifier:
//************************************
void MainObject::HandleMove()
{
  rect_.x += x_val_;

  if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH)
  {
    rect_.x -= x_val_;
  }


  rect_.y += y_val_;
  if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 200)
  {
    rect_.y -= y_val_;
  }
}

void MainObject::RemoveBullet(const int& idx)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    if (idx < p_bullet_list_.size())
   {
      BulletObject* p_bullet = p_bullet_list_.at(idx);
      p_bullet_list_.erase(p_bullet_list_.begin() + idx);

      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
  }
}