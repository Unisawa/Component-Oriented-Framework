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
static GameObject* pObject[4] = {};

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

    Render2DDX* pRender2D0 = pObject[0]->AddComponent<Render2DDX>();
    pRender2D0->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF));
    pRender2D0->SetTexture("Field000.jpg");
    pRender2D0->SetVertex();

    pObject[1] = new GameObject("BBBBB");
    pObject[1]->transform->SetPosition(Vector3(-Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));

    Render2DDX* pRender2D1 = pObject[1]->AddComponent<Render2DDX>();
    pRender2D1->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF));
    pRender2D1->SetTexture("Blade.png");
    pRender2D1->SetVertex();

    pObject[2] = new GameObject("CCCCC");
    pObject[2]->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));

    Render2DDX* pRender2D2 = pObject[2]->AddComponent<Render2DDX>();
    pRender2D2->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF));
    pRender2D2->SetTexture("snow.tga");
    pRender2D2->SetVertex();

    pObject[3] = new GameObject("DDDDD");

    Render2DDX* pRender2D3 = pObject[3]->AddComponent<Render2DDX>();
    pRender2D3->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF / 2));
    pRender2D3->SetTexture("Knife.png");
    pRender2D3->SetVertex();
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
    if (pKey->GetKeyboardTrigger(DIK_Y))
    {
        if (pObject[0] == NULL)
        {
            pObject[0] = new GameObject("AAAAA");

            Render2DDX* pRender2D0 = pObject[0]->AddComponent<Render2DDX>();
            pRender2D0->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF));
            pRender2D0->SetSortingOrder(0.0f);
            pRender2D0->SetTexture("snow.tga");
            pRender2D0->SetVertex();
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_H))
    {
        if (pObject[0] != NULL)
        {
            pObject[0]->Destroy();
            pObject[0] = NULL;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_U))
    {
        if (pObject[1] == NULL)
        {
            pObject[1] = new GameObject("BBBBB");
            pObject[1]->transform->SetPosition(Vector3(-Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));

            Render2DDX* pRender2D1 = pObject[1]->AddComponent<Render2DDX>();
            pRender2D1->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF));
            pRender2D1->SetSortingOrder(1.0f);
            pRender2D1->SetTexture("Blade.png");
            pRender2D1->SetVertex();
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_J))
    {
        if (pObject[1] != NULL)
        {
            pObject[1]->Destroy();
            pObject[1] = NULL;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_I))
    {
        if (pObject[2] == NULL)
        {
            pObject[2] = new GameObject("CCCCC");
            pObject[2]->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));

            Render2DDX* pRender2D2 = pObject[2]->AddComponent<Render2DDX>();
            pRender2D2->SetSize(Vector2(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF));
            pRender2D2->SetSortingOrder(1.0f);
            pRender2D2->SetTexture("Field000.jpg");
            pRender2D2->SetVertex();
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_K))
    {
        if (pObject[2] != NULL)
        {
            pObject[2]->Destroy();
            pObject[2] = NULL;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_F))
    {
        pObject[2]->transform->SetParent(pObject[0]->transform);
    }

    if (pKey->GetKeyboardTrigger(DIK_G))
    {
        pObject[2]->transform->DetachParent();
    }

    if (pKey->GetKeyboardTrigger(DIK_V))
    {
        pObject[2]->transform->SetChild(pObject[1]->transform);
    }

    if (pKey->GetKeyboardTrigger(DIK_B))
    {
        pObject[2]->transform->DetachChildren(pObject[1]->transform);
    }

    if (pKey->GetKeyboardTrigger(DIK_N))
    {
        pObject[2]->transform->SetChild(pObject[3]->transform);
    }

    if (pKey->GetKeyboardTrigger(DIK_M))
    {
        pObject[2]->transform->DetachChildren(pObject[3]->transform);
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