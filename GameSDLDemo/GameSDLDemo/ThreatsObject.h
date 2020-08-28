

#ifndef THREATES_OBJECT_H_
#define THREATES_OBJECT_H_
#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDTH_THREAT 80  // chieu ngang cua enemy
#define HEIGHT_THREAT 33 // chieu cao cua enemy

class ThreatObject : public BaseObject
{
public:
  ThreatObject(); // khoi tao enemy
  ~ThreatObject();// thoat ham va disable enemy

  void HandleMove(const int& x_bordr, const int& y_border); // enemy di chuyen
  void HandleInputAction(SDL_Event events); // auto add enemy vo tran

  void set_x_val(const int& val) {x_val_ = val;} // gan bien x cho vi tri x cua enemy
  void set_y_val(const int& val) {y_val_ = val;} // gan bien y cho vi tri y cua enemy
  int get_x_val() const {return x_val_;}	// cap nhat x cho enemy move
  int get_y_val() const {return y_val_;}	// cap nhat y cho enemy move
  
  // khoi tao, cap nhat va hien thi ammo cua enemy khi khai hoa
  void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;}
  std::vector<BulletObject*> GetBulletList() const {return p_bullet_list_;}

  void InitBullet(BulletObject* p_bullet); // khoi tao 1 ammo
  void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);// tao ra 1 ammo tai vi tri (x,y)
  void Reset(const int& xboder); // delete enemy va lap lai
  void ResetBullet(BulletObject* p_bullet); // delete ammo va lap lai

private:
  int x_val_;
  int y_val_;

  std::vector<BulletObject*> p_bullet_list_;
};

#endif