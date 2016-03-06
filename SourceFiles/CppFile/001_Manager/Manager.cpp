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
#include "001_Manager/Manager.h"

//-----Manager-----//
#include "006_Tool/0060_Input/InputManager.h"
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

GameObjectManager* Manager::pGameObjectManager = NULL;
SceneManager*      Manager::pSceneManager = NULL;

#ifdef USE_DIRECTX
    RenderDXManager* Manager::pRenderDXManager = NULL;
#endif
#ifdef USE_OPENGL
    RenderGLManager* Manager::pRenderGLManager = NULL;
#endif

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
HRESULT Manager::Init()
{
#ifdef USE_DIRECTX
    pRenderDXManager = RenderDXManager::Create();
    if (pRenderDXManager == NULL) return E_FAIL;    // DirectX の初期化に失敗
#endif

#ifdef USE_OPENGL
    pRenderGLManager = RenderGLManager::Create();
    if (pRenderGLManager == NULL) return E_FAIL;    // OpenGL の初期化に失敗
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

#ifdef USE_DIRECTX
    SafeDeleteUninit(pRenderDXManager);
#endif

#ifdef USE_OPENGL
    SafeDeleteUninit(pRenderGLManager);
#endif
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Manager::Update()
{
    pInputManager->Update();

#ifdef USE_DIRECTX
    pRenderDXManager->Update();
#endif

#ifdef USE_OPENGL
    pRenderGLManager->Update();
#endif

    pSceneManager->Update();

    pGameObjectManager->Update();
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void Manager::Draw()
{
#ifdef USE_DIRECTX
    pRenderDXManager->Draw();
#endif

#ifdef USE_OPENGL
    pRenderGLManager->Draw();
#endif
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//