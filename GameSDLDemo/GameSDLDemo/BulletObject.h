
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_
#include "BaseObject.h"

#define WIDTH_LASER 35 // length of the laser ammo
#define HEIGHT_LASER 5 // heigh of the laser ammo

#define WIDTH_SPHERE 10 // length of the phi tieu ammo
#define HEIGHT_SPHERE 10 // length of the phi tieu ammo

class BulletObject : public BaseObject
{
public:
  enum BulletType // kieu load dan ammo
  {
    NONE = 0,	// dan ammo dang load trong gun
    LASER = 1,	// dan ammo loai 1
    SPHERE = 2	// dan ammo loai 2
  };

  BulletObject(); // tao 1 vien dan 
  ~BulletObject(); // disable 1 vien dan
  void HandleInputAction(SDL_Event events); // them 1 vien ammo vao game
  void HandleMove(const int& x_border, const int& y_border); // vien dang moving
  void HandleMoveRightToLeft();	// ammo of enemy moving from right connor to left connor

  int get_type() const {return bullet_type_;} // player click chuot de chon loai dan
  void set_type(const int& type) {bullet_type_ = type;} // set type cho ammo r khai hoa

  bool get_is_move() const {return is_move_;}	// kiem tra duong di cua dan
  void set_is_move(bool is_move) {is_move_ = is_move;} // cap nhap duong di cua dan
  void SetWidthHeight(const int& widht, const int& height) {rect_.w = widht; rect_.h = height;}; // keep the heigh and length of ammo while it moving

  void set_x_val(const int& val) {x_val_ = val;} // gan quy dao x cua ammo
  void set_y_val(const int& val) {y_val_ = val;} // gan quy dao y cua ammo

  int get_x_val() const {return x_val_;}	// cap nhat X cua ammo
  int get_y_val() const {return y_val_;}	// cap nhat Y cua ammo
private:	// tao bien tinh cua ammo
  int x_val_;
  int y_val_;
  int bullet_type_;

  bool is_move_;
};


#endif