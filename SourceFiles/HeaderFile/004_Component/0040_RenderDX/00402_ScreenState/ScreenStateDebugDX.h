﻿/**************************************************************************************************

 @File   : [ ScreenStateDebugDX.h ] 描画する領域を制御するステートクラス (デバッグ用)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _SCREENSTATEDEBUGDX_H_
#define _SCREENSTATEDEBUGDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateDX.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderDXManager;

class ScreenStateDebugDX : public ScreenStateDX
{
public:
             ScreenStateDebugDX();
    virtual ~ScreenStateDebugDX() {}

    virtual void BeginDraw(RenderDXManager* pRender) override { pRender->GetDevice()->SetViewport(&debugViewPort); }

    D3DVIEWPORT9 debugViewPort;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
