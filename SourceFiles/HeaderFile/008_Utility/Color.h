/**************************************************************************************************

 @File   : [ Color.h ] RGBA カラーの表現をするクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _COLOR_H_
#define _COLOR_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
typedef DWORD COLOR;

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class Color
{
public:
    Color() {}
    Color(float R, float G, float B, float A) { r = R; g = G; b = B; a = A; }

    Color operator + (const Color &Vec) const { return Color(r + Vec.r, g + Vec.g, b + Vec.b, a + Vec.a); }
    Color operator - (const Color &Vec) const { return Color(r - Vec.r, g - Vec.g, b - Vec.b, a - Vec.a); }
    Color operator * (float value) const { return Color(r * value, g * value, b * value, a * value); }
    Color operator / (float value) const { return (*this) * (1.0f / value); }

    void operator += (const Color &Vec) { (*this) = (*this) + Vec; }
    void operator -= (const Color &Vec) { (*this) = (*this) - Vec; }
    void operator *= (float value) { (*this) = (*this) * value; }
    void operator /= (float value) { (*this) *= (1.0f / value); }

    void operator = (const Color &Vec) { r = Vec.r; g = Vec.g; b = Vec.b; a = Vec.a; }

    COLOR Trans();

    static Color black;
    static Color White;
    static Color gray;

    static Color red;
    static Color green;
    static Color blue;

    static Color cyan;
    static Color magenta;
    static Color yellow;

    static Color clear;

    float r;
    float g;
    float b;
    float a;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
