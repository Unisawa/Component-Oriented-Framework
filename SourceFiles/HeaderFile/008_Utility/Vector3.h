/**************************************************************************************************

 @File   : [ Vector3.h ] 3Dベクトルと位置の表現
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

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
struct Vector3
{
    Vector3()                          { x = 0.0f; y = 0.0f; z = 0.0f; }
    Vector3(float X, float Y, float Z) { x = X, y = Y; z = Z; }

    Vector3 operator + (const Vector3 &Vec) const { return Vector3(x + Vec.x, y + Vec.y, z + Vec.z); }
    Vector3 operator - (const Vector3 &Vec) const { return Vector3(x - Vec.x, y - Vec.y, z - Vec.z); }
    Vector3 operator * (float value) const { return Vector3(x * value, y * value, z * value); }
    Vector3 operator / (float value) const { return (*this) * (1.0f / value); }

    void operator += (const Vector3 &Vec) { (*this) = (*this) + Vec; }
    void operator -= (const Vector3 &Vec) { (*this) = (*this) - Vec; }
    void operator *= (float value) { (*this) = (*this) * value; }
    void operator /= (float value) { (*this) *= (1.0f / value); }

    void operator  = (const Vector3 &Vec) { x = Vec.x; y = Vec.y; z = Vec.z; }

    void Normalize();

    static Vector3 one;
    static Vector3 zero;

    static Vector3 up;
    static Vector3 down;
    static Vector3 right;
    static Vector3 left;
    static Vector3 forward;
    static Vector3 back;

    float x;
    float y;
    float z;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
