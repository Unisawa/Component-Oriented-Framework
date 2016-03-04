/**************************************************************************************************

 @File   : [ Render2DDX.h ] DirectXで2D四角形ポリゴンを描画するRenderクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDER2DDX_H_
#define _RENDER2DDX_H_

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

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class Render2DDX : public RenderDX
{
public:
             Render2DDX(GameObject* pObject, GameObject::LAYER Layer = GameObject::LAYER::OBJECT2D_OPACITY_ONE);
    virtual ~Render2DDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw()   override;

    //-----Setter, Getter-----//
    void SetTexture(std::string TextureName);
    int  GetTexture() const { return textureID; }

    void  SetColor(Color value) { material.color = value; SetVertex(); }
    void  SetColor(float red, float green, float blue, float alpha) { material.color.r = red; material.color.g = green; material.color.b = blue; material.color.a = alpha; SetVertex(); }
    Color GetColor() const { return material.color; }

    static const std::string className;

private:
    void SetVertex();

    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;    // 頂点バッファ

    D3DXVECTOR2 textureUV;      // テクスチャのUV座標の視点
    int         textureID;      // テクスチャ識別番号
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//