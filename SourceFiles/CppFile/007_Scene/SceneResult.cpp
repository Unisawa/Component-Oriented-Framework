/**************************************************************************************************

 @File   : [ SceneResult.cpp ] タイトルシーンのクラス
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
#include "007_Scene/SceneResult.h"
#include "007_Scene/SceneTitle.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "004_Component/0040_RenderDX/Render2DDX.h"

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
static GameObject* pObject[3] = {};

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
SceneResult::SceneResult()
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
SceneResult::~SceneResult()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void SceneResult::Init()
{
    // GameObjectの生成、コンポーネントの追加テスト
    pObject[0] = new GameObject("AAAAA");
    pObject[0]->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D0 = pObject[0]->AddComponent<Render2DDX>();
    pRender2D0->SetTexture("Field000.jpg");
    pRender2D0->SetVertex();

    pObject[1] = new GameObject("BBBBB");
    pObject[1]->transform->SetPosition(Vector3(-Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));
    pObject[1]->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D1 = pObject[1]->AddComponent<Render2DDX>();
    //pRender2D1->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
    pRender2D1->SetTexture("Blade.png");
    pRender2D1->SetVertex();

    pObject[2] = new GameObject("CCCCC");
    pObject[2]->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));
    pObject[2]->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D2 = pObject[2]->AddComponent<Render2DDX>();
    //pRender2D2->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
    pRender2D2->SetTexture("snow.tga");
    pRender2D2->SetVertex();
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void SceneResult::Uninit()
{
    GameObjectManager::ReleaseAllScene();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void SceneResult::Update()
{
    // 入力テスト
    Keyboard* pKey = InputManager::GetKeyboard();

    // オブジェクト生成
    if (pKey->GetKeyboardTrigger(DIK_Q))
    {
        if (pObject[0] == NULL)
        {
            pObject[0] = new GameObject("AAAAA");
            pObject[0]->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
            Render2DDX* pRender2D0 = pObject[0]->AddComponent<Render2DDX>();
            pRender2D0->SetSortingOrder(0.0f);
            pRender2D0->SetTexture("snow.tga");
            pRender2D0->SetVertex();
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_A))
    {
        if (pObject[0] != NULL)
        {
            pObject[0]->Destroy();
            pObject[0] = NULL;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_W))
    {
        if (pObject[1] == NULL)
        {
            pObject[1] = new GameObject("BBBBB");
            pObject[1]->transform->SetPosition(Vector3(-Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));
            pObject[1]->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
            Render2DDX* pRender2D1 = pObject[1]->AddComponent<Render2DDX>();
            //pRender2D1->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
            pRender2D1->SetSortingOrder(1.0f);
            pRender2D1->SetTexture("Blade.png");
            pRender2D1->SetVertex();
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_S))
    {
        if (pObject[1] != NULL)
        {
            pObject[1]->Destroy();
            pObject[1] = NULL;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_E))
    {
        if (pObject[2] == NULL)
        {
            pObject[2] = new GameObject("CCCCC");
            pObject[2]->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));
            pObject[2]->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
            Render2DDX* pRender2D2 = pObject[2]->AddComponent<Render2DDX>();
            //pRender2D2->SetColor(0.0f, 0.0f, 1.0f, 1.0f);
            pRender2D2->SetSortingOrder(1.0f);
            pRender2D2->SetTexture("Field000.jpg");
            pRender2D2->SetVertex();
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_D))
    {
        if (pObject[2] != NULL)
        {
            pObject[2]->Destroy();
            pObject[2] = NULL;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_SPACE))
    {
        SceneManager::LoadLevel(&Scene::TITLE);
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