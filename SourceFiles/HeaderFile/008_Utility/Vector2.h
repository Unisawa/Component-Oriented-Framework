/**************************************************************************************************

 @File   : [ Vector2.h ] 2Dベクトルと位置の表現
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

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
struct Vector2
{
    Vector2()                 { x = 0.0f; y = 0.0f; }
    Vector2(float X, float Y) { x = X, y = Y; }

    Vector2 operator + (const Vector2 &Vec) const { return Vector2(x + Vec.x, y + Vec.y); }
    Vector2 operator - (const Vector2 &Vec) const { return Vector2(x - Vec.x, y - Vec.y); }
    Vector2 operator * (float value) const { return Vector2(x * value, y * value); }
    Vector2 operator / (float value) const { return (*this) * (1.0f / value); }

    void operator += (const Vector2 &Vec) { (*this) = (*this) + Vec; }
    void operator -= (const Vector2 &Vec) { (*this) = (*this) - Vec; }
    void operator *= (float value) { (*this) = (*this) * value; }
    void operator /= (float value) { (*this) *= (1.0f / value); }

    void operator  = (const Vector2 &Vec) { x = Vec.x; y = Vec.y; }

    static Vector2 one;
    static Vector2 zero;

    static Vector2 up;
    static Vector2 down;
    static Vector2 right;
    static Vector2 left;

    float x;
    float y;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
