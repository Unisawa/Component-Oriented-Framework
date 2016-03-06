/**************************************************************************************************

 @File   : [ RenderDXManager.h ] DirectXの描画を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERDXMANAGER_H_
#define _RENDERDXMANAGER_H_

#ifdef USE_DIRECTX
//***********************************************************************************************//
//                                                                                               //
//  @Link Library                                                                                //
//                                                                                               //
//***********************************************************************************************//
#pragma comment (lib, "d3d9.lib")      // DirectX 本体
#pragma comment (lib, "d3dx9.lib")     // DirectX 拡張ライブラリ
#pragma comment (lib, "dxguid.lib")    // DirectX コンポーネント使用に必要

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----DirectX-----//
#define  D3D_DEBUG_INFO
#include "d3dx9.h"

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
class RenderDX;
class LightDXManager;
class CameraDXManager;
class DebugManagerDX;
class ScreenStateDX;
class TextureDXManager;

class RenderDXManager
{
public:
     RenderDXManager() {}
    ~RenderDXManager() {}

    static RenderDXManager* Create();

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();

    void    SetDefaultViewPort() { pD3DDevice->SetViewport(&defaultViewport); }
    void    ChangeState(ScreenStateDX* pState);

    static void UpdateAll();
    static void DrawAll();
    static void UnLinkListAll();
    static void ReleaseAll();

    static void ZSort();
    static void CalculateZSortAll();

    //-----Operation List-----//
    static void LinkList(RenderDX* pRender, GameObject::LAYER Layer);
    static void UnLinkList(RenderDX* pRender);
    static void Release(RenderDX* pRender);

    //-----Create Font-----//
    static LPD3DXFONT CreateFontText(int CharacterSize, int CharacterWidth, int FontSize, bool IsItalic, std::string FontName);

    //-----Setter, Getter-----//
    static LPDIRECT3DDEVICE9 GetDevice() { return pD3DDevice; }

    static void      SetClearColor(D3DXCOLOR Color) { clearColor = Color; }
    static D3DXCOLOR GetClearColor() { return clearColor; }
    
    static DebugManagerDX*  GetDebugManagerDX()  { return pDebugManagerDX; }

    static LightDXManager*   GetLightDXManager()   { return pLightDXManager; }
    static CameraDXManager*  GetCameraDXManager()  { return pCameraDXManager; }
    static TextureDXManager* GetTextureDXManager() { return pTextureDXManager; }

private:
    static LPDIRECT3D9       pD3DObject;    // Direct3Dオブジェクト
    static LPDIRECT3DDEVICE9 pD3DDevice;    // デバイスオブジェクト

    static D3DVIEWPORT9 defaultViewport;    // 画面の大きさの基本的なビューポート
    static D3DXCOLOR    clearColor;         // 背景クリア色
    
    static DebugManagerDX*  pDebugManagerDX;

    static LightDXManager*   pLightDXManager;
    static CameraDXManager*  pCameraDXManager;
    static TextureDXManager* pTextureDXManager;

    static std::list<RenderDX*> pRenderDXList[GameObject::LAYER_MAX];

    ScreenStateDX* pScreenStateDX;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//