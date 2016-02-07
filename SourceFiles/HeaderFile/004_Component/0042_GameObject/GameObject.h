/**************************************************************************************************

 @File   : [ GameObject.h ] 全ての実体のベースクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----STL-----//
#include <list>

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
class Component;
class Transform;

class GameObject : public Object
{
public:

    static const enum LAYER
    {
        LAYER_ZERO = 0,

        // 3Dオブジェクト-不透明
        OBJECT3D_OPACITY_ONE,
        OBJECT3D_OPACITY_TWO,

        // ビルボード-不透明
        BILLBOARD_OPACITY_ONE,

        // 3Dオブジェクト-半透明
        OBJECT3D_TRANSLUCENT_ONE,
        OBJECT3D_TRANSLUCENT_TWO,

        // ビルボード-半透明
        BILLBOARD_TRANSLUCENT_ONE,

        // 2Dオブジェクト-不透明
        OBJECT2D_OPACITY_ONE,
        OBJECT2D_OPACITY_TWO,

        // 2Dオブジェクト-半透明
        OBJECT2D_TRANSLUCENT_ONE,
        OBJECT2D_TRANSLUCENT_TWO,

        LAYER_MAX
    };

             GameObject(LAYER Layer = LAYER_ZERO);
    virtual ~GameObject();

    virtual void Init();
    virtual void Uninit();
    virtual void Update();

    //-----コンポーネント関連-----//
    void       AddComponent(Component* component);
    Component* GetComponent(std::string name);

    // コンポーネントの追加
    template <typename T> T* AddComponent()
    {
        T* pComponent = new T(this);
        pComponent->ComponentInit();

        componentList.push_back((Component*)pComponent);

        return pComponent;
    }

    // コンポーネントの取得
    template <typename T> T* GetComponent()
    {
        for (auto Iterator = componentList.begin(); Iterator != componentList.end(); ++Iterator)
        {
            if (T::className == (*Iterator)->GetComponentName())
            {
                return (T*)(*Iterator);
            }
        }

        return NULL;
    }

    std::list<Component*> GetComponetList() { return componentList; }

    // GameObject->tag とタグ付けされているか確認
    bool CompareTag(std::string tag) { return ((this->tag == tag) ? true : false); }

    //-----Setter, Getter-----//
    void  SetActive(bool value) { activeSelf = value; }
    bool  GetActive() const { return activeSelf; }

    void  SetLayer(LAYER value) { layer = value; }
    LAYER GetLayer() const { return layer; }

    Transform* GetTransform() { return transform; }

private:
    bool        activeSelf;    // GameObject のローカルのアクティブ状態
    LAYER       layer;         // レイヤー (階層番号 レンダリング順序などに影響する)
    std::string tag;           // タグ名
    Transform*  transform;     // GameObject にアタッチされている Transform

    std::list<Component*> componentList;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//