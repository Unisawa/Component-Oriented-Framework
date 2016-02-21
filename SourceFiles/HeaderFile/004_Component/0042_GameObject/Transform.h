/**************************************************************************************************

 @File   : [ Transform.h ] オブジェクトの位置、回転、スケールを扱うクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "008_Utility/Vector3.h"

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
class GameObject;

class Transform : public Component
{
public:
             Transform(GameObject* pObject = NULL);
    virtual ~Transform();

    void       SetParent(Transform& value);
    Transform* GetParent() { return parent; }

    //-----Setter, Getter-----//
    void    SetPosition(float x, float y, float z) { position.x = x; position.y = y; position.z = z; }
    void    SetPosition(const Vector3 &Vec)        { position = Vec; }
    Vector3 GetPosition() const { return position; }

    void    SetRotation(float x, float y, float z) { rotation.x = x; rotation.y = y; rotation.z = z; }
    void    SetRotation(const Vector3 &Vec)        { rotation = Vec; }
    Vector3 GetRotation() const { return rotation; }

    void    SetScale(float x, float y, float z) { lossyScale.x = x; lossyScale.y = y; lossyScale.z = z; }
    void    SetScale(const Vector3 &Vec)        { lossyScale = Vec; }
    Vector3 GetScale() const { return lossyScale; }

    static const std::string Transform::className;

private:
    Transform* parent;     // Transform の親

    Vector3 position;      // ワールド空間の Transform の位置
    Vector3 rotation;      // ワールド空間の Transform の回転
    Vector3 lossyScale;    // オブジェクトのグローバルスケール
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//