/**************************************************************************************************

 @File   : [ DebugStateRenderDX.h ] 現在表示している描画物の一覧を表示するステートクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _DEBUGSTATERENDERDX_H_
#define _DEBUGSTATERENDERDX_H_

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
class RenderDX;

class DebugStateRenderDX : public DebugStateDX
{
public:
             DebugStateRenderDX() : DebugStateDX() {}
    virtual ~DebugStateRenderDX() {}

    virtual void Init(DebugManagerDX* pDebugManagerDX);
    virtual void Uninit(DebugManagerDX* pDebugManagerDX);
    virtual void Update(DebugManagerDX* pDebugManagerDX);
    virtual void Draw(DebugManagerDX* pDebugManagerDX);

private:
    void CheckRender();
    void CheckRenderChild(GameObject* value);
    void MoveRender();

    std::string messegeHierarchy;
    std::string messegeInspector;

    LPD3DXFONT  pDebugFont;
    D3DXCOLOR   textColor;
    std::string indentSpace;

    GameObject* selectRenderObject;
    int         selectRenderNumber;
    int         selectRenderCount;
    int         maxRenderNumber;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
