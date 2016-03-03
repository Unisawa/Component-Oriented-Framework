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
class Matrix;

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

    void SetUpCamera2D();
    void SetUpCamera3D();

private:
    static std::list<CameraDX*> pCameraDXList;

    // 2D用 Projection, View 行列
    Matrix  orthoProjection;
    Matrix  orthoView;

    // 3D用 Projection, View 行列
    Matrix* pPerspectiveProjection;
    Matrix* pPerspectiveView;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
