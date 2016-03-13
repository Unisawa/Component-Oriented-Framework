/**************************************************************************************************

 @File   : [ DebugStateDX.h ] 各種デバッグの情報を制御するステートクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _DEBUGSTATEDX_H_
#define _DEBUGSTATEDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

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
class DebugManagerDX;
class DebugStateNoneDX;
class DebugStateMenuDX;
class DebugStateGameObjectDX;
class DebugStateRenderDX;

class DebugStateDX
{
public:
             DebugStateDX() {}
    virtual ~DebugStateDX() {}

    virtual void Init(DebugManagerDX* pDebugManagerDX)   = 0;
    virtual void Uninit(DebugManagerDX* pDebugManagerDX) = 0;
    virtual void Update(DebugManagerDX* pDebugManagerDX) = 0;
    virtual void Draw(DebugManagerDX* pDebugManagerDX)   = 0;

    static DebugStateNoneDX       none;
    static DebugStateMenuDX       menu;
    static DebugStateGameObjectDX gameObject;
    static DebugStateRenderDX     render;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
