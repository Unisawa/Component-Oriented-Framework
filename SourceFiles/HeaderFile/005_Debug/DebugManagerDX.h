/**************************************************************************************************

 @File   : [ DebugManagerDX.h ] DirectXのデバッグモードを制御するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _DEBUGMANAGERDX_H_
#define _DEBUGMANAGERDX_H_

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

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class DebugManagerDX
{
public:
     DebugManagerDX();
    ~DebugManagerDX();

    static DebugManagerDX* Create();

    void Init();
    void Uninit();
    void Update();
    void Draw();

    void CheckGameObject();

    static void CheckFPS(DWORD NowTime);
    static void AddframeCount();

    static void Print(std::string String, ...);

private:
    static DWORD currentTime;
    static DWORD lastTimeFPS;
    static DWORD frameCount;
    static int   countFPS;

    static std::string messegeFree;
    static std::string messegeHierarchy;
    static std::string messegeInspector;

    LPD3DXFONT pDebugFont;
    D3DXCOLOR  textColor;
    RECT       freeRect;
    RECT       hierarchyRect;
    RECT       inspectorRect;

    int  selectGameObjectNumber;
    int  maxGameObjectNumber;

    bool isDebugMode;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
