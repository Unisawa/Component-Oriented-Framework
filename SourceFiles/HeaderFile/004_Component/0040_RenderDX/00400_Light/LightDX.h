/**************************************************************************************************

 @File   : [ LightDX.h ] 空間内のライト情報を持つクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _LIGHTDX_H_
#define _LIGHTDX_H_

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
class LightDX : public Behaviour
{
public:

    static const enum LIGHTTYPE
    {
        LIGHTTYPE_DIRECTIONAL = 0,
        LIGHTTYPE_POINT,
        LIGHTTYPE_SPOT,

        LIGHTTYPE_MAX
    };

             LightDX(GameObject* pObject);
    virtual ~LightDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;

    //-----Setter, Getter-----//
    void      SetLightType(LIGHTTYPE value);
    LIGHTTYPE GetLightType() { return lightType; }

    void        SetDirection(D3DXVECTOR3 value) { lightParam.Direction = value; }
    D3DXVECTOR3 GetDirection() { return lightParam.Direction; }
    D3DXVECTOR4 GetDirectionEX();

    void      SetAmbient(D3DXCOLOR value) { lightParam.Ambient = value; }
    D3DXCOLOR GetAmbient() { return lightParam.Ambient; }

    void      SetDiffuse(D3DXCOLOR value) { lightParam.Diffuse = value; }
    D3DXCOLOR GetDiffuse() { return lightParam.Diffuse; }

    void      SetSpecular(D3DXCOLOR value) { lightParam.Specular = value; }
    D3DXCOLOR GetSpecular() { return lightParam.Specular; }

    int GetLightID() { return lightID; }

    static const std::string className;

private:
    LIGHTTYPE lightType;     // ライトの種類
    D3DLIGHT9 lightParam;    // ライトの情報

    int lightID;    // 使用している光源の識別番号
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
