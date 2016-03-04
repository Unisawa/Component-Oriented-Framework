/**************************************************************************************************

 @File   : [ MatrixDX.h ] 一般的な4x4の行列 Matrix クラスの定義
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MATRIXDX_H_
#define _MATRIXDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"

//-----Object-----//
#include "008_Utility/Vector3.h"

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
class Matrix : public D3DXMATRIX
{
public:

    Matrix() : D3DXMATRIX(identity) {}
    Matrix( float _11, float _12, float _13, float _14,
            float _21, float _22, float _23, float _24,
            float _31, float _32, float _33, float _34,
            float _41, float _42, float _43, float _44) :
            D3DXMATRIX(_11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44) {}

    Matrix operator + (const Matrix &mtx) const;
    Matrix operator - (const Matrix &mtx) const;
    Matrix operator * (float f) const;
    Matrix operator * (const Matrix &mtx) const;
    Matrix operator / (const Matrix &mtx) const;

    void operator  += (const Matrix &mtx);
    void operator  -= (const Matrix &mtx);
    void operator  *= (float value);
    void operator  *= (const Matrix &mtx);
    void operator  /= (const Matrix &mtx);
    void operator   = (const Matrix &mtx);

    void operator   = (const D3DXMATRIX &v);

    void   Identity();
    Matrix Inverse();

    void SetTranslate(const Vector3 &Vec);
    void SetScaling  (const Vector3 &Vec);
    void SetRotateYawPitchRoll(const Vector3 &Vec);
    void GetRoll(float x);
    void GetPitch(float y);
    void GetYaw(float z);

    static Matrix identity;
    static Matrix zero;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
