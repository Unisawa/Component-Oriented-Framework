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
             GameObject(std::string Name, LAYER Layer = LAYER_ZERO);
    virtual ~GameObject();

    virtual void Init();
    virtual void Uninit();
    virtual void Update();

    virtual void Destroy(float time = 0.0f) override;
    virtual void Destroy(Component* pComponent, float time = 0.0f);

    static GameObject* Find(std::string Name);

    // コンポーネントの追加
    template <typename T> T* AddComponent()
    {
        T* pComponent = new T(this);
        pComponent->ComponentInit();

        pComponentList.push_back(pComponent);

        return pComponent;
    }

    // コンポーネントの取得
    template <typename T> T* GetComponent()
    {
        for (auto Iterator = pComponentList.begin(); Iterator != pComponentList.end(); ++Iterator)
        {
            if (T::className == (*Iterator)->GetComponentName())
            {
                return (T*)(*Iterator);
            }
        }

        return NULL;
    }

    std::list<Component*> GetComponetList() { return pComponentList; }

    // 指定した文字列(tag) とタグ付けされているか確認
    bool CompareTag(std::string tag) { return ((this->tag == tag) ? true : false); }

    //-----Setter, Getter-----//
    void  DontDestroyOnLoad(bool value) { dontDestroyFlag = value; }
    bool  IsDontDestroy() { return dontDestroyFlag; }

    void  SetActive(bool value) { activeSelf = value; }
    bool  GetActive() const { return activeSelf; }

    void  SetLayer(LAYER value);
    LAYER GetLayer() const { return layer; }

    Transform*  transform;          // GameObject にアタッチされている Transform

private:
    bool        activeSelf;         // GameObject のローカルのアクティブ状態
    LAYER       layer;              // レイヤー (階層番号 レンダリング順序などに影響する)
    std::string tag;                // タグ名
    bool        dontDestroyFlag;    // シーン読み込み時に自動でオブジェクトを削除しない

    std::list<Component*> pComponentList;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//