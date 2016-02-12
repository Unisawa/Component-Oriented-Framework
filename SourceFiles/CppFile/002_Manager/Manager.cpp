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

//-----Manager-----//
#include "006_Tool/0060_Input/InputManager.h"
#include "004_Component/0040_RenderDX/RenderManagerDX.h"
#include "004_Component/0041_RenderGL/RenderManagerGL.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"
#include "007_Scene/SceneManager.h"

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
InputManager* Manager::pInputManager = NULL;

RenderManagerDX* Manager::pRenderManagerDX = NULL;
RenderManagerGL* Manager::pRenderManagerGL = NULL;

GameObjectManager* Manager::pGameObjectManager = NULL;
SceneManager*      Manager::pSceneManager      = NULL;

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

    pInputManager = InputManager::Create();

    pGameObjectManager = GameObjectManager::Create();

    pSceneManager = SceneManager::Create();

    return S_OK;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Manager::Uninit()
{
    SafeDeleteUninit(pSceneManager);

    SafeDeleteUninit(pGameObjectManager);

    SafeDeleteUninit(pInputManager);

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
    pInputManager->Update();

    pSceneManager->Update();

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