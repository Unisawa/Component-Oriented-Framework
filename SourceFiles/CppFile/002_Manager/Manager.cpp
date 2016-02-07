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
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0040_RenderDX/RenderManagerDX.h"
#include "004_Component/0041_RenderGL/RenderManagerGL.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"
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

    GameObject* pTemp = new GameObject;
    pTemp->SetName("AAAAA");
    Render2DDX* pRender2D = pTemp->AddComponent<Render2DDX>();

    GameObject* apTemp = new GameObject;
    apTemp->SetName("BBBBB");

    return S_OK;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Manager::Uninit()
{
#ifdef _DIRECTX
    SafeDeleteUninit(pRenderManagerDX);
#endif

#ifdef _OPENGL
    SafeDeleteUninit(pRenderManagerGL);
#endif

    SafeDeleteUninit(pGameObjectManager);
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