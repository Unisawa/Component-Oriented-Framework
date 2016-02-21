/**************************************************************************************************

 @File   : [ CameraDX.cpp ] 空間内のカメラ情報を持つクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"
#include "001_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/00401_Camera/CameraDX.h"
#include "004_Component/0040_RenderDX/00401_Camera/CameraDXManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
const std::string CameraDX::className = "CameraDX";

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
CameraDX::CameraDX(GameObject* pObject) : Behaviour(pObject, className)
{
    CameraDXManager::LinkList(this);
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
CameraDX::~CameraDX()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void CameraDX::Init()
{
    // 初期値
    PointEye     = D3DXVECTOR3(0.0f, 200.0f, -200.0f);
    PointLook    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    UpVector     = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    Rotation     = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    Length       = sqrtf((PointEye.x - PointLook.x) * (PointEye.x - PointLook.x) +
                         (PointEye.y - PointLook.y) * (PointEye.y - PointLook.y) +
                         (PointEye.z - PointLook.z) * (PointEye.z - PointLook.z));

    D3DXVec3Normalize(&Direction, &(PointLook - PointEye));

    ScreenAspect = (float)Constant::SCREEN_WIDTH / Constant::SCREEN_HEIGHT;
    ScreenNear   = 1.0f;
    ScreenFar    = 10000.0f;
    ScreenAngle  = 45.0f;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void CameraDX::Uninit()
{
    CameraDXManager::UnLinkList(this);
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void CameraDX::Update()
{
    SetProjection();
    SetModelView();
}

/*===============================================================================================* 
  @Summary: カメラのプロジェクション行列を作成し設定する
  @Details: None
 *===============================================================================================*/
void CameraDX::SetProjection()
{
    // デバイスの取得
    LPDIRECT3DDEVICE9  pDevice = RenderManagerDX::GetDevice();

    // プロジェクションマトリックスの設定
    D3DXMatrixIdentity(&ProjectionMatrix);
    D3DXMatrixPerspectiveFovLH(&ProjectionMatrix, ScreenAngle, ScreenAspect, ScreenNear, ScreenFar);
    pDevice->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
}

/*===============================================================================================* 
  @Summary: カメラのモデルビュー行列を作成し設定する
  @Details: None
 *===============================================================================================*/
void CameraDX::SetModelView()
{
    // デバイスの取得
    LPDIRECT3DDEVICE9  pDevice = RenderManagerDX::GetDevice();

    // ビューマトリックスの設定
    D3DXMatrixIdentity(&ViewMatrix);
    D3DXMatrixLookAtLH(&ViewMatrix, &PointEye, &PointLook, &UpVector);
    pDevice->SetTransform(D3DTS_VIEW, &ViewMatrix);
}

/*===============================================================================================* 
  @Summary: あるオブジェクトのカメラからの距離を計算して返す
  @Details: None
 *===============================================================================================*/
float CameraDX::GetZLengthCamera(Vector3 Position)
{
    float       ZLength;
    D3DXVECTOR3 Look;
    D3DXVECTOR3 Pos;

    Pos.x = Position.x;
    Pos.y = Position.y;
    Pos.z = Position.z;

    D3DXVec3Subtract(&Look, &PointLook, &PointEye);
    D3DXVec3Normalize(&Look, &Look);

    ZLength  = D3DXVec3Dot(&Pos, &Look);
    ZLength -= D3DXVec3Dot(&PointEye, &Look);

    return ZLength;
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
