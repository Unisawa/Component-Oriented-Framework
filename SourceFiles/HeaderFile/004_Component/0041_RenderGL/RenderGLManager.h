/**************************************************************************************************

 @File   : [ RenderGLManager.h ] OpneGLの描画を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERGLMANAGER_H_
#define _RENDERGLMANAGER_H_

#ifdef USE_OPENGL
//***********************************************************************************************//
//                                                                                               //
//  @Link Library                                                                                //
//                                                                                               //
//***********************************************************************************************//
#pragma comment (lib, "OpenGL32.lib")    // OpenGL  関連
#pragma comment (lib, "GLu32.lib")       // OpenGL  関連

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----OpenGL-----//
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

//-----Object-----//
#include "004_Component/0042_GameObject/GameObject.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderGL;

class RenderGLManager
{
public:
     RenderGLManager() {}
    ~RenderGLManager() {}

    static RenderGLManager* Create();

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();

    static void UpdateAll();
    static void DrawAll();
    static void UnLinkListAll();
    static void ReleaseAll();

    static void ZSort();
    static void CalculateZSortAll();

    //-----Operation List-----//
    static void LinkList(RenderGL* pRender, GameObject::LAYER Layer);
    static void UnLinkList(RenderGL* pRender);
    static void Release(RenderGL* pRender);

private:
    static HDC   hDC;       // デバイスコンテキスト
    static HGLRC hGLRC;     // カレントコンテキスト

    static std::list<RenderGL*> pRenderGLList[GameObject::LAYER_MAX];
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//