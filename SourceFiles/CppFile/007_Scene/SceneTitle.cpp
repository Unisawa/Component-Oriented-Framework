/**************************************************************************************************

 @File   : [ SceneTitle.cpp ] タイトルシーンのクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "002_Constant/Constant.h"

//-----Manager-----//
#include "006_Tool/0060_Input/InputManager.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"
#include "007_Scene/SceneManager.h"
#include "007_Scene/SceneTitle.h"
#include "007_Scene/SceneGame.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "004_Component/0040_RenderDX/00410_Base/Render2DDX.h"

#include "004_Component/0041_RenderGL/Render2DGL.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
static GameObject* pTemp = NULL;

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
SceneTitle::SceneTitle()
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
SceneTitle::~SceneTitle()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void SceneTitle::Init()
{
#ifdef USE_DIRECTX
    // GameObjectの生成、コンポーネントの追加テスト
    GameObject* pGameObject0 = new GameObject("GameObject A");\

    Render2DDX* pRender2D0 = pGameObject0->AddComponent<Render2DDX>();
    pRender2D0->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF / 2));
    pRender2D0->SetTexture("FractalField000.bmp");
    pRender2D0->SetVertex();

    GameObject* pGameObject1 = new GameObject("GameObject B");
    pGameObject1->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));

    Render2DDX* pRender2D1 = pGameObject1->AddComponent<Render2DDX>();
    pRender2D1->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF / 2));
    pRender2D1->SetTexture("Blade.png");
    pRender2D1->SetVertex();

    GameObject* pGameObject2 = new GameObject("GameObject C");
    pGameObject2->transform->SetPosition(Vector3(-Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));

    Render2DDX* pRender2D2 = pGameObject2->AddComponent<Render2DDX>();
    pRender2D2->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF / 2));
    pRender2D2->SetTexture("Knife.png");
    pRender2D2->SetVertex();

    pTemp = pGameObject0;

    //GameObject* pGameObject9 = new GameObject;
    //pGameObject9->SetName("OpenGL");
    //pGameObject9->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //Render2DGL* pRender2D9 = pGameObject9->AddComponent<Render2DGL>();
    //pRender2D9->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF));
#endif
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void SceneTitle::Uninit()
{
    GameObjectManager::ReleaseAllScene();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void SceneTitle::Update()
{
    // 入力テスト
    Keyboard* pKey = InputManager::GetKeyboard();

    if (pKey->GetKeyboardTrigger(DIK_SPACE))
    {
        SceneManager::LoadLevel(&Scene::GAME);
    }
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
