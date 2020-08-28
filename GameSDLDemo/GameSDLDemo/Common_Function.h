
#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#define GA_FAILED -1
#define GA_SUCCESS 0;


//Screen
const int WIDTH_BACKGROUND  = 4800; // Background rong
const int HEIGHT_BACKGROUND = 600;	// Background cao
const int SCREEN_WIDTH      = 1200; // chieu rong cua man hinh
const int SCREEN_HEIGHT     = 600; // chieu cao cua man hinh
const int SCREEN_BPP        = 32;
const int SPEED_SCREEN      = 1; // speed tua man hinh background

//Main
const int POS_X_START_MAIN_OBJ  = 100; // vi tri x cua player khi start game
const int POS_Y_START_MAIN_OBJ  = 200;	// vi tri x cua player khi start game
const int SPEED_MAIN_OBJECT     = 10;	// toc do cua player
const int SPEED_BULLET_MAIN     = 20;	// toc do ban cua player

//Threats

const int SPEED_THREAT = 3;	// Toc do cua enemy
const int NUM_THREATS  = 3;	// so luong enemy xuat hien cung 1 luc
const int SPEED_BULLET_THREATS          = 10;	// toc do ammo bay cua enemy
const int VAL_OFFSET_START_POST_THREATS = 400;	// vi tri enemy xuat hien tu goc phai cua window game
const int UNDER_LIMIT_THREAT = 200;	// vi tri y toi thieu ma enemy duoc bay khi xuat hien

static SDL_Surface* g_screen    = NULL;	// load img cua cac player, enemy
static SDL_Surface* g_bkground  = NULL;	// load background
static SDL_Event g_even;				// update load cac su kien trong game

static Mix_Chunk* g_sound_bullet[2];	// load sound cua gun
static Mix_Chunk* g_sound_exp[2];		// load sound cua explosion


static char g_name_bk_ground[] = {"bk2.png"};	// vi tri cua Background

static char g_name_main_obj[]           = {"plane_fly.png"};	// img cua player
static char g_name_exp_main []          = {"exp_main.png"};		// img cua explosion
static char g_name_bullet_main_laser[]  = {"laser.png"};		// img cua laser ammo
static char g_name_bullet_main_fire[]   = {"sphere.png"};		// img cua phi tieu
static char g_name_audio_bullet_main[]  = {"Laser.wav"};		// sound cua laser ammo
static char g_name_audio_bullet_main2[] = {"Fire1.wav"};		// sound cua phi tieu ammo
static char g_name_audio_exp_main[]     = {"Bomb1.wav"};		// sound cua bom roi -- chua co 

static char g_name_exp_threats[]        = {"exp.png"};			// img explosion cua enemy
static char g_name_threats[]            = {"af1.png"};			// img cua enemy
static char g_name_bullet_threats[]     = {"sphere2.png"};		// img ammo cua enemy
static char g_name_audio_exp_threats[]  = {"Explosion+1.wav"};	// sound cua enemy

namespace SDLCommonFunc
{
  SDL_Surface* LoadImage(std::string file_path);  // load img background 
  void CleanUp();	// Clear man hinh
  void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);// Load screen
  void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);// Tua background
  bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);// Kiem tra cac va cham tu vat the trong game
  int MakeRandValue(const int& div_val = 400);// Khung trong cua game
}


#endif
