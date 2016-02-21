/**************************************************************************************************

 @File   : [ Manager.h ] ゲーム全般に必要な各種Managerを管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MANAGER_H_
#define _MANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0041_RenderGL/RenderGLManager.h"
#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define _DIRECTX    // DirectXの使用宣言
//#define _OPENGL     // OpenGL の使用宣言

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class InputManager;

class RenderDXManager;
class RenderGLManager;
class GameObjectManager;
class SceneManager;

class Manager
{
public:
     Manager() {}
    ~Manager() {}

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();

    static InputManager* GetInputManager() { return pInputManager; }

    static RenderDXManager* GetRenderDXManager() { return pRenderDXManager; }
    static RenderGLManager* GetRenderGLManager() { return pRenderGLManager; }

    static GameObjectManager* GetGameObjectManager() { return pGameObjectManager; }
    static SceneManager*      GetSceneManager() { return pSceneManager; }

private:
    static InputManager* pInputManager;

    static RenderDXManager* pRenderDXManager;
    static RenderGLManager* pRenderGLManager;

    static GameObjectManager* pGameObjectManager;
    static SceneManager*      pSceneManager;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//