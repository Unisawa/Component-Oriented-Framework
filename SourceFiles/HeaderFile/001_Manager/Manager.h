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

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define USE_DIRECTX    // DirectXの使用宣言
//#define USE_OPENGL     // OpenGL の使用宣言

#ifdef USE_DIRECTX
    #include "004_Component/0040_RenderDX/RenderDXManager.h"
    #include "008_Utility/MatrixDX.h"
#endif

#ifdef USE_OPENGL
    #include "004_Component/0041_RenderGL/RenderGLManager.h"
    #include "008_Utility/MatrixGL.h"
#endif

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class InputManager;
class GameObjectManager;
class SceneManager;

#ifdef USE_DIRECTX
    class RenderDXManager;
#endif
#ifdef USE_OPENGL
    class RenderGLManager;
#endif

class Manager
{
public:
     Manager() {}
    ~Manager() {}

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();

    static InputManager*      GetInputManager() { return pInputManager; }

    static GameObjectManager* GetGameObjectManager() { return pGameObjectManager; }
    static SceneManager*      GetSceneManager() { return pSceneManager; }

#ifdef USE_DIRECTX
    static RenderDXManager* GetRenderDXManager() { return pRenderDXManager; }
#endif
#ifdef USE_OPENGL
    static RenderGLManager* GetRenderGLManager() { return pRenderGLManager; }
#endif

private:
    static InputManager*      pInputManager;

    static GameObjectManager* pGameObjectManager;
    static SceneManager*      pSceneManager;

#ifdef USE_DIRECTX
    static RenderDXManager* pRenderDXManager;
#endif
#ifdef USE_OPENGL
    static RenderGLManager* pRenderGLManager;
#endif
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//