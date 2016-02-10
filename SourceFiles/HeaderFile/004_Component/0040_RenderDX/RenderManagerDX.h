/**************************************************************************************************

 @File   : [ RenderManagerDX.h ] DirectXの描画を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERMANAGERDX_H_
#define _RENDERMANAGERDX_H_

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

class RenderManagerDX
{
public:
     RenderManagerDX() {}
    ~RenderManagerDX() {}

    static RenderManagerDX* Create();

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
    static void LinkList(RenderDX* pRender, GameObject::LAYER Layer);
    static void UnLinkList(RenderDX* pRender);
    static void Release(RenderDX* pRender);

    //-----Create Font-----//
    static LPD3DXFONT CreateFontText(int CharacterSize, int CharacterWidth, int FontSize, bool IsItalic, std::string FontName);

    //-----Setter, Getter-----//
    static LPDIRECT3DDEVICE9 GetDevice() { return pD3DDevice; }

    static void      SetClearColor(D3DXCOLOR Color) { clearColor = Color; }
    static D3DXCOLOR GetClearColor() { return clearColor; }

private:
    static LPDIRECT3D9       pD3DObject;    // Direct3Dオブジェクト
    static LPDIRECT3DDEVICE9 pD3DDevice;    // デバイスオブジェクト

    static D3DXCOLOR clearColor;            // 背景クリア色

    static std::list<RenderDX*> renderDXList[GameObject::LAYER_MAX];
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//