/**************************************************************************************************

 @File   : [ Vector4.h ] 4次元ベクトルの表現
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _VECTOR4_H_
#define _VECTOR4_H_

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
struct Vector4
{
    Vector4()                                   { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
    Vector4(float X, float Y, float Z, float W) { x = X, y = Y; z = Z; w = W; }

    Vector4 operator + (const Vector4 &Vec) const { return Vector4(x + Vec.x, y + Vec.y, z + Vec.z, w + Vec.w); }
    Vector4 operator - (const Vector4 &Vec) const { return Vector4(x - Vec.x, y - Vec.y, z - Vec.z, w - Vec.w); }
    Vector4 operator * (float value) const { return Vector4(x * value, y * value, z * value, w * value); }
    Vector4 operator / (float value) const { return (*this) * (1.0f / value); }

    void operator += (const Vector4 &Vec) { (*this) = (*this) + Vec; }
    void operator -= (const Vector4 &Vec) { (*this) = (*this) - Vec; }
    void operator *= (float value) { (*this) = (*this) * value; }
    void operator /= (float value) { (*this) *= (1.0f / value); }

    void operator  = (const Vector4 &Vec) { x = Vec.x; y = Vec.y; z = Vec.z; w = Vec.w; }

    static Vector4 one;
    static Vector4 zero;

    float x;
    float y;
    float z;
    float w;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
