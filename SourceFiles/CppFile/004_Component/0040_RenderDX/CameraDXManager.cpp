/**************************************************************************************************

 @File   : [ CameraDXManager.cpp ] CameraDXを管理するクラス
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
#include "004_Component/0040_RenderDX/CameraDX.h"
#include "004_Component/0040_RenderDX/CameraDXManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************/
std::list<CameraDX*> CameraDXManager::pCameraDXList;

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
CameraDXManager *CameraDXManager::Create()
{
    CameraDXManager* pCameraDXManager;
    pCameraDXManager = new CameraDXManager();
    pCameraDXManager->Init();

    return pCameraDXManager;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void CameraDXManager::Init()
{
    // 初期カメラの生成
    GameObject* pCameraGameObject = new GameObject("MainCamera");
    pCameraGameObject->AddComponent<CameraDX>();
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void CameraDXManager::Uninit()
{
    ReleaseAll();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void CameraDXManager::Update()
{
    UpdateAll();
}

/*===============================================================================================*
  @Summary: 登録された全てのCameraDXを更新する
  @Details: None
 *===============================================================================================*/
void CameraDXManager::UpdateAll()
{
    for (auto Iterator = pCameraDXList.begin(); Iterator != pCameraDXList.end(); ++Iterator)
    {
        (*Iterator)->Update();
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのCameraDXを削除する
  @Details: None
 *===============================================================================================*/
void CameraDXManager::ReleaseAll()
{
    CameraDX* pCameraDX;

    for (auto Iterator = pCameraDXList.begin(); Iterator != pCameraDXList.end();)
    {
        pCameraDX = (*Iterator);

        // リストから切り離す
        Iterator = pCameraDXList.erase(Iterator);

        // GameObjectの削除
        SafeDeleteUninit(pCameraDX);
    }

    pCameraDXList.clear();
}

/*===============================================================================================*
  @Summary: CameraDXをリストに追加する
  @Details: None
 *===============================================================================================*/
void CameraDXManager::LinkList(CameraDX* pCameraDX)
{
    pCameraDXList.push_back(pCameraDX);
}

/*===============================================================================================*
  @Summary: CameraDXをリストから解除する
  @Details: None
 *===============================================================================================*/
void CameraDXManager::UnLinkList(CameraDX* pCameraDX)
{
    for (auto Iterator = pCameraDXList.begin(); Iterator != pCameraDXList.end(); ++Iterator)
    {
        if ((*Iterator) == pCameraDX)
        {
            // リストから切り離す
            pCameraDXList.erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: 対象のCameraDXを削除する (リストからも取り除く)
  @Details: 対象のCameraDXのUninit()が呼ばれる
 *===============================================================================================*/
void CameraDXManager::Release(CameraDX* pCameraDX)
{
    for (auto Iterator = pCameraDXList.begin(); Iterator != pCameraDXList.end();)
    {
        if ((*Iterator) == pCameraDX)
        {
            // リストから切り離す
            Iterator = pCameraDXList.erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pCameraDX);

            return;
        }

        ++Iterator;
    }
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
