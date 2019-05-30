#include "Serial_Com_func.h"
#include "DxLib.h"
#include <algorithm>
#include <math.h>
using namespace std;
//#define	COM_PORT	"COM5"
//#define	COM_SPEED	38400
#include "Ball.h"
#include "Bar.h"
#include "hCOM_class.h"

int window_w = 640, window_h = 480,game_flag =0 ;

class Fps {
	int mStartTime;         //測定開始時刻
	int mCount;             //カウンタ
	float mFps;             //fps
	static const int N = 60;//平均を取るサンプル数
	static const int FPS = 60;	//設定したFPS

public:
	Fps() {
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	bool Update() {
		if (mCount == 0) { //1フレーム目なら時刻を記憶
			mStartTime = GetNowCount();
		}
		if (mCount == N) { //60フレーム目なら平均を計算する
			int t = GetNowCount();
			mFps = 1000.f / ((t - mStartTime) / (float)N);
			mCount = 0;
			mStartTime = t;
		}
		mCount++;
		return true;
	}

	void Draw() {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
	}

	void Wait() {
		int tookTime = GetNowCount() - mStartTime;	//かかった時間
		int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
		if (waitTime > 0) {
			Sleep(waitTime);	//待機
		}
	}
};





// プログラムは WinMain から始まります
int main()
{
	Fps fps;
	hCOM_class *Com_port = new hCOM_class();
	
	int box_x = (window_w/2)-50, box_y= window_h - 50;
	Ball *ball = new Ball();
	Bar *bar = new Bar();

	SetGraphMode(window_w, window_h, 16);
	ChangeWindowMode(1);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);



	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		fps.Update();	//更新
		fps.Draw();		//描画
		Com_port->get_packet();
		Com_port->parse_packet();
		if (Com_port->get_switch_status() && game_flag != 2) { game_flag = 1;}
		switch (game_flag) {
		case 0:
			DrawString(window_w / 2-100,window_h / 2, "Use the toggle switch to start game!",GetColor(255,255,255)); break;
		case 1:
			if (!ball->get_game_end_flag()) {
				ball->Update();
				bar->Update(Com_port->get_parsed_data());
				ball->wall_collision_detect();
				bar->Ball_detection(ball);
				DrawCircle(ball->get_x(), ball->get_y(), ball->get_radius(), GetColor(255, 255, 255));
				DrawBox(bar->Get_top_left_x(),
					bar->Get_top_left_y(),
					bar->Get_top_left_x() + bar->Get_width(),
					bar->Get_top_left_y() + bar->Get_height(),
					GetColor(255, 255, 255), 1);
			}
			else {
				game_flag = 2;
			}
			break;
		case 2:
			DrawString(window_w / 2 - 100, window_h / 2, "Gameover!!", GetColor(255, 255, 255)); ScreenFlip(); goto gameend;
		default:
			break;
		}
		ScreenFlip();
		fps.Wait();
	}

	gameend:
	WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	
	return 0;				// ソフトの終了 
}
