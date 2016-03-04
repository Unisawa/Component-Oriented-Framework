/**************************************************************************************************

 @File   : [ Render3DDX.h ] DirectXで3D四角形ポリゴンを描画するRenderクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDER3DDX_H_
#define _RENDER3DDX_H_

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
class Render3DDX : public RenderDX
{
public:
             Render3DDX(GameObject* pObject, GameObject::LAYER Layer = GameObject::LAYER::OBJECT3D_OPACITY_ONE);
    virtual ~Render3DDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw()   override;

    //-----Setter, Getter-----//
    void SetTexture(std::string TextureName);
    int  GetTexture() const { return textureID; }

    void      SetSize(Vector3 value) { size = value; }
    void      SetSize(float x, float y, float z) { size.x = x; size.y = y; size.z = z; }
    Vector3   GetSize() { return size; }

    void  SetColor(Color value) { material.color = value; };
    void  SetColor(float red, float green, float blue, float alpha) { material.color.r = red; material.color.g = green; material.color.b = blue; material.color.a = alpha; SetVertex(); }
    Color GetColor() const { return material.color; }

    static const std::string className;

private:
    void SetVertex();

    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;    // 頂点バッファ

    Vector3     size;           // ポリゴンの大きさ

    D3DXVECTOR2 textureUV;      // テクスチャのUV座標の視点
    int         textureID;      // テクスチャ識別番号
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//