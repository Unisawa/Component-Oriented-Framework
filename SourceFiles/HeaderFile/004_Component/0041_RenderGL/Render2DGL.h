/**************************************************************************************************

 @File   : [ Render2DGL.h ] OpenGL��2D�l�p�`�|���S����`�悷��Render�N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDER2DGL_H_
#define _RENDER2DGL_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0041_RenderGL/RenderGL.h"

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
class Render2DGL : public RenderGL
{
public:
             Render2DGL(GameObject* pObject, GameObject::LAYER Layer = GameObject::LAYER::OBJECT2D_OPACITY_ONE);
    virtual ~Render2DGL();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw()   override;

    //-----Setter, Getter-----//
    void SetTexture(std::string TextureName);
    int  GetTexture() const { return textureID; }

private:
    int textureID;    // �e�N�X�`�����ʔԍ�
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//