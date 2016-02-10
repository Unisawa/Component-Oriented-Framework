/**************************************************************************************************

 @File   : [ Manager.cpp ] ゲーム全般に必要な各種管理クラスを管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "001_Constant/Constant.h"
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0040_RenderDX/RenderManagerDX.h"
#include "004_Component/0041_RenderGL/RenderManagerGL.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"
#include "004_Component/0040_RenderDX/Render2DDX.h"
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
RenderManagerDX* Manager::pRenderManagerDX = NULL;
RenderManagerGL* Manager::pRenderManagerGL = NULL;

GameObjectManager* Manager::pGameObjectManager = NULL;

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
HRESULT Manager::Init()
{
#ifdef _DIRECTX
    pRenderManagerDX = RenderManagerDX::Create();
    if (pRenderManagerDX == NULL) return E_FAIL;    // DirectX の初期化に失敗
#endif

#ifdef _OPENGL
    pRenderManagerGL = RenderManagerGL::Create();
    if (pRenderManagerGL == NULL) return E_FAIL;    // OpenGL の初期化に失敗
#endif

    pGameObjectManager = GameObjectManager::Create();

    GameObject* pGameObject0 = new GameObject;
    pGameObject0->SetName("AAAAA");
    pGameObject0->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    pGameObject0->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D0 = pGameObject0->AddComponent<Render2DDX>();

    GameObject* pGameObject1 = new GameObject;
    pGameObject1->SetName("BBBBB");
    pGameObject1->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF + Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    pGameObject1->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D1 = pGameObject1->AddComponent<Render2DDX>();
    pRender2D1->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

    GameObject* pGameObject2 = new GameObject;
    pGameObject2->SetName("CCCCC");
    pGameObject2->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF - Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    pGameObject2->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    Render2DDX* pRender2D2 = pGameObject2->AddComponent<Render2DDX>();
    pRender2D2->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

    // コンポーネントテスト
    Render2DDX* Temp = pGameObject2->GetComponent<Render2DDX>();
    Temp->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

    //GameObject* pGameObject9 = new GameObject;
    //pGameObject9->SetName("OpenGL");
    //pGameObject9->GetTransform()->SetPosition(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject9->GetTransform()->SetScale(D3DXVECTOR3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DGL* pRender2D9 = pGameObject9->AddComponent<Render2DGL>();

    return S_OK;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Manager::Uninit()
{
    SafeDeleteUninit(pGameObjectManager);

#ifdef _DIRECTX
    SafeDeleteUninit(pRenderManagerDX);
#endif

#ifdef _OPENGL
    SafeDeleteUninit(pRenderManagerGL);
#endif
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Manager::Update()
{
    pGameObjectManager->Update();

#ifdef _DIRECTX
    pRenderManagerDX->Update();
#endif

#ifdef _OPENGL
    pRenderManagerGL->Update();
#endif
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void Manager::Draw()
{
#ifdef _DIRECTX
    pRenderManagerDX->Draw();
#endif

#ifdef _OPENGL
    pRenderManagerGL->Draw();
#endif
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//