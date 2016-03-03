/**************************************************************************************************

 @File   : [ SceneGame.cpp ] ゲームシーンのクラス
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
#include "004_Component/0040_RenderDX/Render2DDX.h"
#include "004_Component/0040_RenderDX/Render3DDX.h"

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
static Render3DDX* pRender3D3 = NULL;

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
SceneGame::SceneGame()
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
SceneGame::~SceneGame()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void SceneGame::Init()
{
    // GameObjectの生成、コンポーネントの追加テスト
    //GameObject* pGameObject0 = new GameObject;
    //pGameObject0->SetName("AAAAA");
    //pGameObject0->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject0->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DDX* pRender2D0 = pGameObject0->AddComponent<Render2DDX>();

    //GameObject* pGameObject1 = new GameObject;
    //pGameObject1->SetName("BBBBB");
    //pGameObject1->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF + Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject1->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DDX* pRender2D1 = pGameObject1->AddComponent<Render2DDX>();
    //pRender2D1->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

    //GameObject* pGameObject2 = new GameObject;
    //pGameObject2->SetName("CCCCC");
    //pGameObject2->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF - Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject2->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DDX* pRender2D2 = pGameObject2->AddComponent<Render2DDX>();
    //pRender2D2->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

    //pTemp = pGameObject2;

    //GameObject* pGameObject9 = new GameObject;
    //pGameObject9->SetName("OpenGL");
    //pGameObject9->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject9->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DGL* pRender2D9 = pGameObject9->AddComponent<Render2DGL>();

    // 3Dポリゴン描画テスト
    GameObject* pGameObject3 = new GameObject("DDDDD");

    pRender3D3 = pGameObject3->AddComponent<Render3DDX>();
    pRender3D3->SetSize(100.0f, 0.0f, 100.0f);
    pRender3D3->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
    
    GameObject* pGameObject4 = new GameObject("FFFFF");

    pRender3D3 = pGameObject4->AddComponent<Render3DDX>();
    pRender3D3->transform->SetPosition(100.0f, 10.0f, 0.0f);
    pRender3D3->SetSize(100.0f, 0.0f, 100.0f);
    pRender3D3->SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

    pTemp = pGameObject3;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void SceneGame::Uninit()
{
    GameObjectManager::ReleaseAllScene();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void SceneGame::Update()
{
    // 入力テスト
    Keyboard* pKey = InputManager::GetKeyboard();

    // コンポーネント追加テスト
    if (pKey->GetKeyboardTrigger(DIK_C))
    {
        Vector3 Pos = pTemp->transform->GetPosition();
        Pos.x -= 1.0f;
        pTemp->transform->SetPosition(Pos);
    }

    // コンポーネント取得テスト
    if (pKey->GetKeyboardTrigger(DIK_V))
    {
        Vector3 Pos = pTemp->transform->GetPosition();
        Pos.x += 1.0f;
        pTemp->transform->SetPosition(Pos);
    }

    // ゲームオブジェクトの削除テスト
    if (pKey->GetKeyboardTrigger(DIK_K))
    {
        pTemp->Destroy();
    }

    // コンポーネントの削除テスト
    if (pKey->GetKeyboardTrigger(DIK_L))
    {
        Render2DDX* pRender = pTemp->GetComponent<Render2DDX>();
        pRender->Destroy();
    }

    if (pKey->GetKeyboardTrigger(DIK_SPACE))
    {
        SceneManager::LoadLevel(&Scene::TITLE);
    }
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//