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
#include "002_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/00401_Camera/CameraDX.h"
#include "004_Component/0040_RenderDX/00401_Camera/CameraDXManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

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
    D3DXMatrixOrthoLH(&orthoProjection, Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT, 0.1f, 500.0f);
    D3DXMatrixLookAtLH(&orthoView, &D3DXVECTOR3(0, 0, -250), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));

    // MainCamera の生成
    GameObject* pCameraGameObject = new GameObject("MainCamera");
    pCameraGameObject->transform->SetPosition(0.0f, 100.0f, -200.0f);
    pCameraGameObject->transform->SetRotation(0.55f, 0.0f, 0.0f);
    pCameraGameObject->DontDestroyOnLoad(true);

    CameraDX* pCamera = pCameraGameObject->AddComponent<CameraDX>();
    pPerspectiveProjection = &pCamera->ProjectionMatrix;
    pPerspectiveView       = &pCamera->ViewMatrix;

    //GameObject* pGameObject = new GameObject("Camera");
    //pCameraGameObject->transform->SetParent(pGameObject->transform);
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

/*===============================================================================================* 
  @Summary: Projection, View 行列を設定する
  @Details: None
 *===============================================================================================*/
void CameraDXManager::SetUpCamera2D()
{
    // デバイスの取得
    LPDIRECT3DDEVICE9  pDevice = RenderDXManager::GetDevice();

    pDevice->SetTransform(D3DTS_PROJECTION, &orthoProjection);
    pDevice->SetTransform(D3DTS_VIEW, &orthoView);
}

/*===============================================================================================* 
  @Summary: Projection, View 行列を設定する
  @Details: None
 *===============================================================================================*/
void CameraDXManager::SetUpCamera3D()
{
    // デバイスの取得
    LPDIRECT3DDEVICE9  pDevice = RenderDXManager::GetDevice();

    pDevice->SetTransform(D3DTS_PROJECTION, pPerspectiveProjection);
    pDevice->SetTransform(D3DTS_VIEW, pPerspectiveView);
}

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
