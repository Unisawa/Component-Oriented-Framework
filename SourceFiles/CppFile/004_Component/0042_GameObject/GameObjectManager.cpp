/**************************************************************************************************

 @File   : [ GameObjectManager.cpp ] 全ての実体を管理クラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----Object-----//
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
std::list<GameObject*> GameObjectManager::gameObjectList[GameObject::LAYER_MAX];

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
GameObjectManager *GameObjectManager::Create()
{
    GameObjectManager* pGameObjectManager;
    pGameObjectManager = new GameObjectManager();
    pGameObjectManager->Init();

    return pGameObjectManager;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void GameObjectManager::Init()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        gameObjectList[Layer].clear();
    }
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void GameObjectManager::Uninit()
{
    ReleaseAll();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void GameObjectManager::Update()
{
    UpdateAll();
}

/*===============================================================================================*
  @Summary: 登録された全てのGameObjectを更新する
  @Details: None
 *===============================================================================================*/
void GameObjectManager::UpdateAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end(); ++Iterator)
        {
            if ((*Iterator)->GetActive())
            {
                (*Iterator)->Update();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのGameObjectを削除する
  @Details: None
 *===============================================================================================*/
void GameObjectManager::ReleaseAll()
{
    GameObject* pObject;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end();)
        {
            pObject = (*Iterator);

            // リストから切り離す
            Iterator = gameObjectList[Layer].erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pObject);
        }

        gameObjectList[Layer].clear();
    }
}

/*===============================================================================================*
  @Summary: GameObjectをリストに追加する
  @Details: None
 *===============================================================================================*/
void GameObjectManager::LinkList(GameObject* pObject, GameObject::LAYER Layer)
{
    gameObjectList[Layer].push_back(pObject);
}

/*===============================================================================================*
  @Summary: GameObjectをリストから解除する
  @Details: None
 *===============================================================================================*/
void GameObjectManager::UnLinkList(GameObject* pObject)
{
    GameObject::LAYER Layer = pObject->GetLayer();

    for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end(); ++Iterator)
    {
        if (*Iterator == pObject)
        {
            // リストから切り離す
            gameObjectList[Layer].erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: 対象のGameObjectを削除する (リストからも取り除く)
  @Details: 対象のGameObjectのUninit()が呼ばれる
 *===============================================================================================*/
void GameObjectManager::Release(GameObject* pObject)
{
    GameObject::LAYER Layer = pObject->GetLayer();

    for (auto Iterator = gameObjectList[Layer].begin(); Iterator != gameObjectList[Layer].end();)
    {
        if (*Iterator == pObject)
        {
            // リストから切り離す
            Iterator = gameObjectList[Layer].erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pObject);

            return;
        }

        ++Iterator;
    }
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