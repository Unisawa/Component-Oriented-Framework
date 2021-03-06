﻿/**************************************************************************************************

 @File   : [ LightDX.cpp ] 空間内のライト情報を持つクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/00400_Light/LightDX.h"
#include "004_Component/0040_RenderDX/00400_Light/LightDXManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
const std::string LightDX::className = "LightDX";

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
LightDX::LightDX(GameObject* pObject) : Behaviour(pObject, className)
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
LightDX::~LightDX()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void LightDX::Init()
{
    lightType = LIGHTTYPE_DIRECTIONAL;
    lightID = LightDXManager::LinkList(this);

    // ライトの初期化
    ZeroMemory(&lightParam, sizeof(D3DLIGHT9));

    lightParam.Type     = D3DLIGHT_DIRECTIONAL;                 // 光源の種類
    lightParam.Ambient  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // 環境光 (間接光)
    lightParam.Diffuse  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // 拡散反射光
    lightParam.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);    // 鏡面反射

    D3DXVec3Normalize((D3DXVECTOR3*)&lightParam.Direction, &D3DXVECTOR3(0.0f, -1.0f, 1.0f));    // 各値を正規化する

    // デバイスオブジェクトの取得
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    pDevice->SetLight(lightID, &lightParam);    // ライトの設定
    pDevice->LightEnable(lightID, TRUE);        // ライトの有効
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void LightDX::Uninit()
{
    LightDXManager::UnLinkList(this);

    // ライトの無効
    RenderDXManager::GetDevice()->LightEnable(lightID, FALSE);
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void LightDX::Update()
{

}

/*===============================================================================================* 
  @Summary: Light の種類を設定する
  @Details: None
 *===============================================================================================*/
void LightDX::SetLightType(LIGHTTYPE value)
{
    lightType = value;

    switch (value)
    {
        case LIGHTTYPE_DIRECTIONAL:
            lightParam.Type = D3DLIGHT_DIRECTIONAL;
            break;

        case LIGHTTYPE_POINT:
            lightParam.Type = D3DLIGHT_POINT;
            break;

        case LIGHTTYPE_SPOT:
            lightParam.Type = D3DLIGHT_SPOT;
            break;
    }

    RenderDXManager::GetDevice()->SetLight(lightID, &lightParam);
}

/*===============================================================================================* 
  @Summary: ライトが向いている方向を取得する
  @Details: シェーダー等で D3DXVECTOR4型 を使用する場合はこちらを使う
 *===============================================================================================*/
D3DXVECTOR4 LightDX::GetDirectionEX()
{
    D3DXVECTOR4 Vec;

    Vec.x = lightParam.Direction.x;
    Vec.y = lightParam.Direction.y;
    Vec.z = lightParam.Direction.z;
    Vec.w = 1.0f;

    return Vec;
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
