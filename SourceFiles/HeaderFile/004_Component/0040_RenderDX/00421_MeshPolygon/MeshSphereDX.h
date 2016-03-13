/**************************************************************************************************

 @File   : [ MeshSphereDX.h ] 球状のメッシュを生成するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MESHFIELDDX_H_
#define _MESHFIELDDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/00420_Mesh/MeshFilterDX.h"

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
class MeshSphereDX : public MeshFilterDX
{
public:
             MeshSphereDX(GameObject* pObject);
    virtual ~MeshSphereDX();

    virtual void Init()   override;
    virtual void Uninit() override;
    virtual void Update() override;

    void  SetUpVertex();
    void  SetUpSphere(int DivX, int DivY, float Radius);

    //-----Setter, Getter-----//
    void  SetRadius(float value) { radius = value; }
    float GetRadius() const { return radius; }

    void  SetNormalDirection(float value) { normalDirection = value; }
    float GetNormalDirection() const { return normalDirection; }

    static const std::string className;

private:
    float radius;             // 球の半径
    float normalDirection;    // 法線の方向 内側(+1)か外側(-1)か？
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
