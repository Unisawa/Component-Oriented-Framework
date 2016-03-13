/**************************************************************************************************

 @File   : [ MeshFilterDX.h ] メッシュを描画するためのクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MESHFILTERDX_H_
#define _MESHFILTERDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Component.h"

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
class MeshDX;
class MeshRenderDX;
class Texture;

class MeshFilterDX : public Component
{
public:
             MeshFilterDX(GameObject* pObject, std::string ComponentName);
    virtual ~MeshFilterDX();

    virtual void Init()   override {}
    virtual void Uninit() override {}
    virtual void Update() override {}

    //-----Setter, Getter-----//
    void     SetTexture(std::string value);
    void     SetTexture(Texture* value);
    Texture* GetTexture();

    MeshRenderDX* GetMeshRender() { return pMeshRender; }

protected:
    MeshDX*       pMesh;
    MeshRenderDX* pMeshRender;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
