
#include "Common_Function.h"

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path)
{
  SDL_Surface * load_image = NULL; // bien load image
  SDL_Surface* optimize_image = NULL; // bien toi uu optimize img
  load_image = IMG_Load(file_path.c_str()); // link load file
  if (load_image != NULL) // ko load dc img thi load lai
  {
    optimize_image= SDL_DisplayFormat(load_image);
    SDL_FreeSurface(load_image);

    if (optimize_image != NULL) // load dc thi optimize theo window
    {
      UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF); // compile img ra pixel tren cmd
      SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key); // in color len pixel
    }
  }
  return optimize_image; // img dc load len window
}


void SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{ // tao be mat do hoa trong game
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset); // vi tri hien thi cua background va cac item
}

void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{ // cac day update hinh anh dynamic trong game
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, clip, des, &offset);
}



bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{ // ktra va cham trong game
  int left_a = object1.x; // goc trai cua vat a
  int right_a = object1.x + object1.w; // goc phai cua vat a
  int top_a = object1.y; // top cua vat a
  int bottom_a = object1.y + object1.h; // day cua vat a

  int left_b = object2.x; // trai cua vat b
  int right_b = object2.x + object2.w; // phai cua vat b
  int top_b = object2.y; // dinh cua vat b
  int bottom_b = object2.y + object2.h; // day cua vat b

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  { // A va cham b
    return true;
  }

  return false;
}


int SDLCommonFunc::MakeRandValue(const int& div_val /*400*/)
{
  int rand_y = rand()%div_val;
  if (rand_y > SCREEN_HEIGHT - 200)
  {
    rand_y = SCREEN_HEIGHT*0.3;
  }
  return rand_y;
}


void SDLCommonFunc::CleanUp()
{ // giai phong hien thi de update frame moi
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
}