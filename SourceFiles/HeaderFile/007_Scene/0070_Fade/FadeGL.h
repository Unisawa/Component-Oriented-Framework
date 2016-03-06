/**************************************************************************************************

 @File   : [ FadeGL.h ] 画面全体の照度を変化させるフェードクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _FADEGL_H_
#define _FADEGL_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "007_Scene/0070_Fade/Fade.h"

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
class Render2DGL;
class Color;

class FadeGL : public Fade
{
public:
             FadeGL(GameObject* pObject);
    virtual ~FadeGL();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;

    void FadeIn();
    void FadeOut();

    void SetColor(Color value);

    static const std::string className;

private:
    void UpdateFadeIn()  override;
    void UpdateFadeOut() override;

    Render2DGL* pRender2D;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//