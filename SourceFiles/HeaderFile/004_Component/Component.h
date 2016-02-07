/**************************************************************************************************

 @File   : [ Component.h ] GameObject にアタッチされる全てに対するベースのクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----Object-----//
#include "003_Object/Object.h"

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
class Transform;

class Component : public Object
{
public:
    enum ComponentType
    {
        ComponentTransform = 0,
        ComponentRenderer,
        ComponentCollider,
        ComponentNetwork,
        ComponentRigidbody,
        ComponentParticleSystem,
        ComponentScript,
        ComponentTypeCamera,
        ComponentTypeLight,
        ComponentMax,
    };

             Component() {}
             Component(ComponentType type, GameObject* gameObject);
    virtual ~Component();

    virtual void Init()   {}
    virtual void Uninit() {}
    virtual void Update() {}

    const std::string& GetComponentName() { return componentName; }

    GameObject*   gameObject;    // アタッチしているGameObject
    std::string   tag;           // GameObjectのタグ
    Transform*    transform;     // GameObject にアタッチされた Transform

private:
    std::string   componentName;
    ComponentType componentType;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//