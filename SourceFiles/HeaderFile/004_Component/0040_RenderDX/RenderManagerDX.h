/**************************************************************************************************

 @File   : [ RenderManagerDX.h ] DirectX�̕`����Ǘ�����N���X
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
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

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

    static LPDIRECT3DDEVICE9 GetDevice() { return pD3DDevice; }

    static void      SetClearColor(D3DXCOLOR Color) { clearColor = Color; }
    static D3DXCOLOR GetClearColor() { return clearColor; }

private:
    static LPDIRECT3D9       pD3DObject;    // Direct3D�I�u�W�F�N�g
    static LPDIRECT3DDEVICE9 pD3DDevice;    // �f�o�C�X�I�u�W�F�N�g

    static D3DXCOLOR clearColor;            // �w�i�N���A�F
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//