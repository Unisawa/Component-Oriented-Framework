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
        ComponentBehaviour,

        ComponentMax,
    };

             Component(GameObject* pObject, ComponentType Type, std::string ComponentName);
    virtual ~Component();

    virtual void Init()   {}
    virtual void Uninit() {}
    virtual void Update() {}

    virtual void ComponentInit()   { Init(); }
    virtual void ComponentUninit() { Uninit(); }
    virtual void ComponentUpdate() { Update(); }

    virtual void Destroy(float time = 0.0f) override;

    // コンポーネント関連
    template <typename T> T* GetComponent()
    {
        std::list<Component*> pComponentList = gameObject->GetComponetList();

        for (auto Iterator = pComponentList.begin(); Iterator != pComponentList.end(); ++Iterator)
        {
            if (T::className == (*Iterator)->GetComponentName())
            {
                return (T*)(*Iterator);
            }
        }

        return NULL;
    }

    void        SetComponentName(std::string value) { componentName = value; }
    std::string GetComponentName() const { return componentName; }

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