/**************************************************************************************************

 @File   : [ CameraDXManager.h ] CameraDXを管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _CAMERADXMANAGER_H_
#define _CAMERADXMANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0040_RenderDX/00401_Camera/CameraDX.h"

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
class CameraDX;

class CameraDXManager
{
public:
     CameraDXManager() {}
    ~CameraDXManager() {}

    static CameraDXManager* Create();

    void Init();
    void Uninit();
    void Update();

    static void UpdateAll();
    static void UnLinkListAll();
    static void ReleaseAll();

    //-----Operation List-----//
    static void LinkList(CameraDX* pCameraDX);
    static void UnLinkList(CameraDX* pCameraDX);
    static void Release(CameraDX* pCameraDX);

    static std::list<CameraDX*> GetCameraDXList() { return pCameraDXList; }

private:
    static std::list<CameraDX*> pCameraDXList;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
