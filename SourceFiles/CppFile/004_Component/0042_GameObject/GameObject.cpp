/**************************************************************************************************

 @File   : [ GameObject.cpp ] 全ての実体のベースクラス
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
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"

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

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
GameObject::GameObject(LAYER Layer)
{
    activeSelf      = true;
    transform       = new Transform(this);
    dontDestroyFlag = false;
    layer           = Layer;

    SetName("GameObject (Default)");

    GameObjectManager::LinkList(this, Layer);
}

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
GameObject::GameObject(std::string Name, LAYER Layer)
{
    activeSelf      = true;
    transform       = new Transform(this);
    dontDestroyFlag = false;
    layer           = Layer;

    SetName(Name);

    GameObjectManager::LinkList(this, Layer);
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
GameObject::~GameObject()
{
    SafeDelete(transform);
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void GameObject::Init()
{

}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void GameObject::Uninit()
{
    Component* pComponent;

    for (auto Iterator = pComponentList.begin(); Iterator != pComponentList.end();)
    {
        pComponent = (*Iterator);

        // コンポーネントの削除
        SafeDeleteUninit(pComponent);

        Iterator++;
    }
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void GameObject::Update()
{
    // 所持している各コンポーネントの更新処理
    for (auto Iterator = pComponentList.begin(); Iterator != pComponentList.end();)
    {
        (*Iterator)->ComponentUpdate();

        Iterator++;
    }
}

/*===============================================================================================* 
  @Summary: GameObject の削除
  @Details: None
 *===============================================================================================*/
void GameObject::Destroy(float time)
{
    GameObjectManager::Release(this);
}

/*===============================================================================================* 
  @Summary: Component の削除
  @Details: None
 *===============================================================================================*/
void GameObject::Destroy(Component* pComponent, float time)
{
    for (auto Iterator = pComponentList.begin(); Iterator != pComponentList.end();)
    {
        if (pComponent == (*Iterator))
        {
            // リストから切り離す
            Iterator = pComponentList.erase(Iterator);

            // コンポーネントの削除
            SafeDeleteUninit(pComponent);

            return;
        }

        Iterator++;
    }
}

/*===============================================================================================* 
  @Summary: 指定した名前を持つ GameObject を検索してオブジェクトを返す
  @Details: None
 *===============================================================================================*/
GameObject* GameObject::Find(std::string Name)
{
    return GameObjectManager::FindGameObject(Name);
}

/*===============================================================================================* 
  @Summary: Layer (更新順) を変更する
  @Details: None
 *===============================================================================================*/
void GameObject::SetLayer(LAYER value)
{
    if (layer == value) return;

    GameObjectManager::UnLinkList(this);
    layer = value;
    GameObjectManager::LinkList(this, value);
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//