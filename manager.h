//*****************************************************************************
//  managerモジュール
//  author: 中島将浩
//  update: 2014/05/07
//*****************************************************************************
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"


//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class Scene;
class SceneFactory;
class Input;
class Joypad;

class Manager{
public:
	//*****************************************************************************
	//【コンストラクタ】
	//  第1引数: れんだらー
	//*****************************************************************************
	Manager(){
	}

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~Manager(){}

	//*****************************************************************************
	//【初期化】
	//  返り値: 初期化に成功したかどうか
	//  引数: なし
	//*****************************************************************************
	static HRESULT SetUp(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

	//*****************************************************************************
	//【終了】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static void Release(void);

	//*****************************************************************************
	//【更新】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static void Update(void);

	//*****************************************************************************
	//【描画】
	//  返り値: なし
	//  引数: なし
	//*****************************************************************************
	static void Draw(void);

	//accessor
	static void SetSceneFactory(SceneFactory *src){_factory = src;}
	static bool SceneFactoryExist(void){return (_factory != NULL);}
private:
	static Renderer *_renderer;
	static Scene *_cur_scene;
	static SceneFactory *_factory;//ファクトリー

	static Input *_input;

	static void Change(void);
	/*使用例
	void Title::Update(void){
		if(Input::GetTrigger(DIK_RETURN)){
			//ゲームへ
			Manager::SetSceneFactory(new GameFactory());
			Fade::FadeOut();
		}
	}
	*/
};


#endif//_MANAGER_H_