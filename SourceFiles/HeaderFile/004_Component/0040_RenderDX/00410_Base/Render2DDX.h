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
#include "004_Component/0040_RenderDX/00410_Base/RenderDX.h"
#include "008_Utility/Vector2.h"

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
class Render2DDX : public RenderDX
{
public:
             Render2DDX(GameObject* pObject, GameObject::LAYER Layer = GameObject::LAYER::OBJECT2D_OPACITY_ONE);
    virtual ~Render2DDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;
    virtual void Draw()   override;

    virtual void SetVertex() override;

    //-----Setter, Getter-----//
    void  SetColor(Color value) { material.color = value; SetVertex(); }
    void  SetColor(float red, float green, float blue, float alpha) { material.color.r = red; material.color.g = green; material.color.b = blue; material.color.a = alpha; SetVertex(); }
    Color GetColor() const { return material.color; }

    void    SetSize(float x, float y) { size.x = x; size.y = y; }
    void    SetSize(const Vector2 &Vec)        { size = Vec; }
    Vector2 GetSize() const { return size; }

    static const std::string className;

private:
    LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;    // 頂点バッファ

    Vector2 size;    // 2Dポリゴンの大きさ
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//