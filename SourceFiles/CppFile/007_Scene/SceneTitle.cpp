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
    // GameObjectの生成、コンポーネントの追加テスト
    GameObject* pGameObject0 = new GameObject;
    pGameObject0->SetName("AAAAA");
    //pGameObject0->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    pGameObject0->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D0 = pGameObject0->AddComponent<Render2DDX>();

    GameObject* pGameObject1 = new GameObject("BBBBB");
    pGameObject1->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));
    pGameObject1->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D1 = pGameObject1->AddComponent<Render2DDX>();
    pRender2D1->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
    //pGameObject1->DontDestroyOnLoad(true);

    GameObject* pGameObject2 = new GameObject;
    pGameObject2->SetName("CCCCC");
    pGameObject2->transform->SetPosition(Vector3(-Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));
    pGameObject2->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D2 = pGameObject2->AddComponent<Render2DDX>();
    pRender2D2->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

    pTemp = pGameObject2;

    //GameObject* pGameObject9 = new GameObject;
    //pGameObject9->SetName("OpenGL");
    //pGameObject9->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject9->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DGL* pRender2D9 = pGameObject9->AddComponent<Render2DGL>();

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

    // コンポーネント追加テスト
    if (pKey->GetKeyboardTrigger(DIK_C))
    {
        if (pTemp != NULL)
        {
            Render2DDX* pRender = pTemp->GetComponent<Render2DDX>();

            if (pRender == NULL)
                pTemp->AddComponent<Render2DDX>()->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
        }
    }

    // コンポーネント取得テスト
    if (pKey->GetKeyboardTrigger(DIK_V))
    {
        if (pTemp != NULL)
        {
            Render2DDX* pRender = pTemp->GetComponent<Render2DDX>();

            if (pRender != NULL)
                pRender->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
        }
    }

    // ゲームオブジェクトの検索テスト
    if (pKey->GetKeyboardTrigger(DIK_H))
    {
        pTemp = GameObject::Find("BBBBB");
    }

    // ゲームオブジェクトの生成テスト
    if (pKey->GetKeyboardTrigger(DIK_J))
    {
        if (pTemp == NULL)
        {
            GameObject* pGameObject0 = new GameObject("CCCCC");
            pGameObject0->transform->SetPosition(Vector3(-Constant::SCREEN_WIDTH_HALF / 2, 0.0f, 0.0f));
            pGameObject0->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
            Render2DDX* pRender2D2 = pGameObject0->AddComponent<Render2DDX>();
            pRender2D2->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

            pTemp = pGameObject0;
        }
    }

    // ゲームオブジェクトの削除テスト
    if (pKey->GetKeyboardTrigger(DIK_K))
    {
        if (pTemp != NULL)
        {
            pTemp->Destroy();
            pTemp = NULL;
        }
    }

    // コンポーネントの削除テスト
    if (pKey->GetKeyboardTrigger(DIK_L))
    {
        if (pTemp != NULL)
        {
            Render2DDX* pRender = pTemp->GetComponent<Render2DDX>();

            if (pRender != NULL)
                pRender->Destroy();
        }
    }

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