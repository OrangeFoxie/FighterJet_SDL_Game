
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Common_Function.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 77 //Chieu dai cua phi co player
#define HEIGHT_MAIN_OBJECT 52 // Chieu rong cua phi co player

class MainObject : public BaseObject
{
public:
  MainObject();	// Tao ham main object
  ~MainObject();// Thoat ham main object

  void HandleInputAction(SDL_Event events, Mix_Chunk* bullet_sound[2]);	// Chen am thanh vao game
  void HandleMove(); // Ham di chuyen cua vat the
  void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list_ = bullet_list;} // Danh sach cac loai bullet
  std::vector<BulletObject*> GetBulletList() const {return p_bullet_list_;}	// tao quy dao di chuyen cua bullet
  void MakeBullet(SDL_Surface* des);	// Tao 1 bullet
  void RemoveBullet(const int& idx);	// Delete 1 bullet
private:
  int x_val_;	// truc X
  int y_val_;	// reuc Y

  std::vector<BulletObject*> p_bullet_list_;

};



#endif //MAIN_OBJECT_H_