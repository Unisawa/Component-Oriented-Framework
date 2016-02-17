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
#ifndef _CameraDX_H_
#define _CameraDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0043_Behaviour/Behaviour.h"

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

    virtual float GetZLengthCamera(D3DXVECTOR3 Position);

    virtual D3DXMATRIX GetProjectionMatrix() { return ProjectionMatrix; }
    virtual D3DXMATRIX GetViewMatrix()       { return ViewMatrix; }

    static const std::string className;

    D3DXMATRIX  ProjectionMatrix;    // プロジェクションマトリックス
    D3DXMATRIX  ViewMatrix;          // ビューマトリックス

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
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
