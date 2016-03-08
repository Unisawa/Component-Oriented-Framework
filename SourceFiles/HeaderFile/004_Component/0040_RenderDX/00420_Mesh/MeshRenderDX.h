/**************************************************************************************************

 @File   : [ MeshRenderDX.h ] 
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MESHRENDERDX_H_
#define _MESHRENDERDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderDX.h"

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

class MeshRenderDX : public RenderDX
{
public:
             MeshRenderDX(GameObject* pObject, GameObject::LAYER Layer = GameObject::LAYER::OBJECT3D_OPACITY_ONE);
    virtual ~MeshRenderDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw()   override;

    static const std::string className;

    //-----Setter, Getter-----//
    void     SetMesh(MeshDX* value) { pMesh = value; }
    MeshDX*  GetMesh() { return pMesh; }

    void     SetTexture(std::string value);
    void     SetTexture(Texture* value);
    Texture* GetTexture() { return material.mainTexture; }

private:
    MeshDX* pMesh;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
