/**************************************************************************************************

 @File   : [ LightDXManager.h ] LightDXを管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _LIGHTMANAGER_H_
#define _LIGHTMANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0040_RenderDX/00400_Light/LightDX.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define MAX_LIGHT_NUM (8)

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class LightDX;

class LightDXManager
{
public:
     LightDXManager() {}
    ~LightDXManager() {}

    static LightDXManager* Create();

    void Init();
    void Uninit();
    void Update();

    static void UpdateAll();
    static void UnLinkListAll();
    static void ReleaseAll();

    //-----Operation List-----//
    static int  LinkList(LightDX* pLightDX);
    static void UnLinkList(LightDX* pLightDX);
    static void Release(LightDX* pLightDX);

    static void EnableSpecular(BOOL value) { RenderDXManager::GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, value); }

    static LightDX* GetLight(int LightID);

private:
    static std::list<LightDX*> pLightDXList;

    static bool useLightID[MAX_LIGHT_NUM];    // 固定機能パイプライン使用時の8つのライトを管理するフラグ
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
