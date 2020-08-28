
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"

bool Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == GA_FAILED) // neu load cac tai nguyen fail thi out game
  {
    return false;
  }

  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);// tao ra man hinh window de play game

  if (g_screen == NULL)// ko tao dc window thi out game
    return false;

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == GA_FAILED)// khong load dc sound thi out game
    return false;

  //Read file wav audio
  g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_bullet_main);
  g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_bullet_main2);
  g_sound_exp[0] = Mix_LoadWAV(g_name_audio_exp_threats);
  g_sound_exp[1] = Mix_LoadWAV(g_name_audio_exp_main);

  if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[1] == NULL)
  {// ko read dc 1 file sound bat ki thi out game
    return false;
  }

  return true;
}


int main(int arc, char*argv[])
{
  bool is_run_screen = true;// background vs moi thu tua from right to left infinity
  int bkgn_x = 0; // vi tri background img duoi day window
  bool is_quit = false;// game ko thoat
  if (Init() == false)// khong load dc source thi out
    return 0;

  g_bkground = SDLCommonFunc::LoadImage(g_name_bk_ground);// load bg img
  if (g_bkground == NULL)
  {
    return 0;// ko load dc thi out game
  }

  //Make MainObject -- player model
  MainObject plane_object;
  plane_object.SetRect(POS_X_START_MAIN_OBJ, POS_Y_START_MAIN_OBJ);// vi tri cua player luc bat dau game
  bool ret = plane_object.LoadImg(g_name_main_obj);// load img cua player
  if (!ret)
  {
    return 0;// ko load dc img thi out game
  }

  //Init explosion object
  ExplosionObject exp_main;
  ExplosionObject exp_threats;
  ret = exp_main.LoadImg(g_name_exp_main);// load img cua explosion big
  exp_main.set_clip();// tao ra chuoi explosion tu img 
  if (ret == false) return 0;// ko load dc thi out game

  ret = exp_threats.LoadImg(g_name_exp_threats );// load img cua explsion small
  exp_threats.set_clip();// tao ra chuoi explosion tu img
  if (!ret) return 0;// ko load duoc thi out game

  //Make ThreatObject - tao ra enemies
  ThreatObject* p_threats = new ThreatObject[NUM_THREATS];// tao 1 enemy

  for (int t = 0; t < NUM_THREATS; t++)// so luong enemy -- mac dinh la 3
  {
    ThreatObject* p_threat = (p_threats + t);// cong them 1 enemy cho den khi dat dc 3 con
    if (p_threat)// tao dc 1 enemy thi...
    {
      ret = p_threat->LoadImg(g_name_threats);// load img cua enemy
      if (ret == false)// ko load dc thi fail
      {
        delete [] p_threats;// xoa enemy
        SDLCommonFunc::CleanUp();
        SDL_Quit();
        return 0;// reset va lap lai quy trinh tao enemy
      }

      int rand_y = SDLCommonFunc::MakeRandValue();// tao vung di chuyen-space cua enemy
      p_threat->SetRect(SCREEN_WIDTH + t*VAL_OFFSET_START_POST_THREATS, rand_y);// vung di chuyen cua enemy ben trong rand
      p_threat->set_x_val(SPEED_THREAT);// speed cua enemy

      BulletObject* p_bullet = new BulletObject();// tao ra 1 ammo khi enemy fire their flak cannon
      p_threat->InitBullet(p_bullet);// trieu hoi ammo cho enemy
    }
  }

  while (!is_quit) // trong khi game dang choi thi...
  {
    while (SDL_PollEvent(&g_even)) // cap nhat trang thai cua program
    {
      if (g_even.type == SDL_QUIT)// neu nhan duoc lenh quit game...
      {
        is_quit = true;// thi quit game
        break;
      }
      plane_object.HandleInputAction(g_even, g_sound_bullet);// khong thi load cac su kien va source game
    }

    //Implement dynamic screen - tua backgroun
    if (is_run_screen == true)// load man hinh lien tuc
    {
      bkgn_x -= SPEED_SCREEN; // man tua tu right sang left
      if (bkgn_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH))// ktra hien thi 1 phan bg img tren window game, load het img roi thi stop
      {
        is_run_screen = false;
      }
      else
      {// chua load het bg img thi load tiep
        SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
      }
    }
    else
    {// load bg img trong khi game dang choi va chua het bg img nhu thuong le
      SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkgn_x, 0);
    }
    

    //Implement main object -- trieu hoi player vao window
    plane_object.HandleMove();
    plane_object.Show(g_screen);
    plane_object.MakeBullet(g_screen);

    //Implement Threats Object -- trieu hoi enemies vao window
    for (int tt = 0; tt < NUM_THREATS; tt++)// kiem tra xem du enemies chua
    {
      ThreatObject* p_threat = (p_threats + tt);// chua thi them
      if (p_threat)// them dc thi load source cho enemies
      {
        p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);// di chuyen cua enemies
        p_threat->Show(g_screen);// hien thi len window
        p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);// tao ammo cho enemy


        //COLLISION THREAT BULLET -> MAIN OBJECT -- KIEM TRA VIEN DAN CUA ENEMIES BAN TRUNG AI
        bool is_col1 = false;// vien dan khong ban trung ai theo nac dinh
        std::vector<BulletObject*> bullet_arr = p_threat->GetBulletList();// tai list vi tri cua ammo
        for (int am = 0; am < bullet_arr.size(); am++)// lay vi tri cua ammo khi no move
        {
          BulletObject* p_bullet = bullet_arr.at(am);// cap nhat vi tri cua ammo
          if (p_bullet)// neu vien dan dang bay
          {// neu vien border cua ammo va cham voi vien border cua object thi ...
            is_col1 = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), plane_object.GetRect());
            if (is_col1 == true)// va cham mode is on
            {
              p_threat->ResetBullet(p_bullet);// xoa vien dan sau khi va cham
              break;
            }
          }
        }

        //Check collision main and threats -- KIEM TRA XEM PLAYER CO YOLO KAMIKAZE VS ENEMIES KHONG
        bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());// lay vung bao quan cua moi obj
        if (is_col1 || is_col)// neu bi trung dan hoac tong nhau
        {
          for (int ex = 0; ex < 4; ex++)// tao 1 vung explosion
          {// set vi tri cua explosion
            int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) -  EXP_WIDTH*0.5;
            int y_Pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5)- EXP_HEIGHT*0.5;

            exp_main.set_frame(ex);// explsion xuat hien trong 4frame
            exp_main.SetRect(x_pos, y_Pos);// vung no cua explsion
            exp_main.ShowEx(g_screen);// hien thi explosion
            //Update screen
            if ( SDL_Flip(g_screen) == -1)// vien man hinh
            {//  neu obj bi hit thi bi disable
              delete [] p_threats;
              SDLCommonFunc::CleanUp();
              SDL_Quit();
              return 0;
            }
          }

           Mix_PlayChannel(-1, g_sound_exp[1], 0); // am thanh explosion 
          /*if (MessageBox(NULL, L"HU HU Die roi", L"Thua roi :<", MB_OK) == IDOK)
          {
             delete [] p_threats;
             SDLCommonFunc::CleanUp();
             SDL_Quit();
			 return 1;
          }*/
        }

        //Check collision main bullet with threats. -- CHECK PLAYER BAN TRUNG ENEMIES
        std::vector<BulletObject*> bullet_list = plane_object.GetBulletList();// lay danh sach ammo
        for (int im = 0; im < bullet_list.size(); im++)
        {
          BulletObject* p_bullet = bullet_list.at(im);// vi tri cua ammo
          if (p_bullet != NULL)// co ammo dang bay
          {// kiem tra va cham giua ammo va enemy
            bool ret_col = SDLCommonFunc::CheckCollision(p_bullet->GetRect(), p_threat->GetRect());
            if (ret_col)// vung va cham
            {

              for (int tx = 0; tx < 4; tx++)
              {// vung explosion
                int x_pos = p_bullet->GetRect().x - EXP_WIDTH*0.5;
                int y_pos = p_bullet->GetRect().y - EXP_HEIGHT*0.5;

                exp_threats.set_frame(tx);// explosion xuat hien trong 4 frame
                exp_threats.SetRect(x_pos, y_pos);// vung xuat hien cua explosion
                exp_threats.ShowEx(g_screen);// hien thi explosion

                if (SDL_Flip(g_screen) == -1)
                {
                  delete [] p_threats;// xoa enemies bi trung dan
                  SDLCommonFunc::CleanUp();
                  SDL_Quit();
                  return 0;
                }
              }
			  // update window, xoa ammo cua enemy die
              p_threat->Reset(SCREEN_WIDTH + tt*VAL_OFFSET_START_POST_THREATS);
              plane_object.RemoveBullet(im);
              Mix_PlayChannel(-1, g_sound_exp[0], 0);
            }
          }
        }
      }
    }

    //Update screen- xoa cac enemies bi hit hoac ra khoi window
    if ( SDL_Flip(g_screen) == -1)
    {
      delete [] p_threats;
      SDLCommonFunc::CleanUp();
      SDL_Quit();
      return 0;
    }
  }

  delete [] p_threats;
  SDLCommonFunc::CleanUp();
  SDL_Quit();

  return 1;
}