/**************************************************************************************************

 @File   : [ CameraDX.h ] 空間内のカメラ情報を持つクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _CAMERADX_H_
#define _CAMERADX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0043_Behaviour/Behaviour.h"

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
class CameraDX : public Behaviour
{
public:
             CameraDX(GameObject* pObject);
    virtual ~CameraDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;

    virtual void SetProjection();
    virtual void SetModelView();

    virtual float GetZLengthCamera(Vector3 Position);

    virtual Matrix GetProjectionMatrix() { return ProjectionMatrix; }
    virtual Matrix GetViewMatrix()       { return ViewMatrix; }

    static const std::string className;

    Matrix      ProjectionMatrix;    // プロジェクションマトリックス
    Matrix      ViewMatrix;          // ビューマトリックス

    D3DXVECTOR3 PointEye;       // 視点
    D3DXVECTOR3 PointLook;      // 注視点
    D3DXVECTOR3 UpVector;       // 上方向ベクトル

    D3DXVECTOR3 Direction;      // カメラが向いている方向
    D3DXVECTOR3 Rotation;       // 回転方向
    float       Length;         // 視点と注視点との距離

    float ScreenAspect;     // アスペクト比 (スクリーンサイズ比)
    float ScreenNear;       // 前面クリッピング範囲
    float ScreenFar;        // 後面クリッピング範囲
    float ScreenAngle;      // 視野角

private:

};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
