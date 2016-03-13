/**************************************************************************************************

 @File   : [ DebugStateGameObjectDX.h ] 現在表示しているGameObjectの一覧を表示するステートクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _DEBUGSTATEGAMEOBJECTDX_H_
#define _DEBUGSTATEGAMEOBJECTDX_H_

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
class GameObject;

class DebugStateGameObjectDX : public DebugStateDX
{
public:
             DebugStateGameObjectDX() : DebugStateDX() {}
    virtual ~DebugStateGameObjectDX() {}

    virtual void Init(DebugManagerDX* pDebugManagerDX);
    virtual void Uninit(DebugManagerDX* pDebugManagerDX);
    virtual void Update(DebugManagerDX* pDebugManagerDX);
    virtual void Draw(DebugManagerDX* pDebugManagerDX);

    void CheckGameObject();
    void CheckGameObjectChild(GameObject* value);
    void MoveGameObject();

private:
    std::string messegeHierarchy;
    std::string messegeInspector;

    RECT        hierarchyRect;
    RECT        inspectorRect;

    LPD3DXFONT  pDebugFont;
    D3DXCOLOR   textColor;
    std::string indentSpace;

    GameObject* selectGameObject;
    int         selectGameObjectNumber;
    int         selectGameObjectCount;
    int         maxGameObjectNumber;

};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
