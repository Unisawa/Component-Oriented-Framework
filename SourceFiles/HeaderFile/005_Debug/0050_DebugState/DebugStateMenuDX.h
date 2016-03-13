/**************************************************************************************************

 @File   : [ DebugStateMenuDX.h ] 各種デバッグモードの一覧を表示するステートクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _DEBUGSTATEMENUDX_H_
#define _DEBUGSTATEMENUDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "005_Debug/0050_DebugState/DebugStateDX.h"

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

class DebugStateMenuDX : public DebugStateDX
{
public:
             DebugStateMenuDX() : DebugStateDX() {}
    virtual ~DebugStateMenuDX() {}

    virtual void Init(DebugManagerDX* pDebugManagerDX);
    virtual void Uninit(DebugManagerDX* pDebugManagerDX);
    virtual void Update(DebugManagerDX* pDebugManagerDX);
    virtual void Draw(DebugManagerDX* pDebugManagerDX);

private:
    std::string messegeMenu;

    LPD3DXFONT pDebugFont;
    D3DXCOLOR  textColor;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
