/**************************************************************************************************

 @File   : [ Render2DGL.h ] OpenGL‚Å2DŽlŠpŒ`ƒ|ƒŠƒSƒ“‚ð•`‰æ‚·‚éRenderƒNƒ‰ƒX
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
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0041_RenderGL/RenderGL.h"
#include "008_Utility/Vector2.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_OPENGL

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
    void  SetColor(Color value) { material.color = value; }
    void  SetColor(float red, float green, float blue, float alpha) { material.color.r = red; material.color.g = green; material.color.b = blue; material.color.a = alpha; }
    Color GetColor() const { return material.color; }
    
    void    SetSize(float x, float y) { size.x = x; size.y = y; }
    void    SetSize(const Vector2 &Vec) { size = Vec; }
    Vector2 GetSize() const { return size; }

    static const std::string className;

private:
    Vector2 size;    // 2Dƒ|ƒŠƒSƒ“‚Ì‘å‚«‚³
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//