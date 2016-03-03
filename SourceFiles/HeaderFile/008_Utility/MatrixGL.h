/**************************************************************************************************

 @File   : [ MatrixGL.h ] 一般的な4x4の行列 Matrix クラスの定義
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MATRIXGL_H_
#define _MATRIXGL_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "004_Component/0041_RenderGL/RenderGLManager.h"

//-----Object-----//
#include "008_Utility/Vector3.h"

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
struct Matrix
{
    Matrix();
    Matrix( float _11, float _12, float _13, float _14,
            float _21, float _22, float _23, float _24,
            float _31, float _32, float _33, float _34,
            float _41, float _42, float _43, float _44 );

    Matrix operator + (const Matrix &mtx) const;
    Matrix operator - (const Matrix &mtx) const;
    Matrix operator * (float value) const;
    Matrix operator * (const Matrix &mtx) const;

    void operator += (const Matrix &mtx);
    void operator -= (const Matrix &mtx);
    void operator *= (float value);
    void operator *= (const Matrix &mtx);
    void operator  = (const Matrix &mtx);

    void Identity();
    void Inverse();
    void SetTranslate(const Vector3 &Vec);
    void SetScaling  (const Vector3 &Vec);
    void SetRotateYawPitchRoll(const Vector3 &Vec);

    static Matrix GetRoll(float x);
    static Matrix GetPitch(float y);
    static Matrix GetYaw(float z);

    static Matrix identity;
    static Matrix zero;

    float _11; float _12; float _13; float _14;
    float _21; float _22; float _23; float _24;
    float _31; float _32; float _33; float _34;
    float _41; float _42; float _43; float _44;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
