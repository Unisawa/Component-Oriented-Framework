/**************************************************************************************************

 @File   : [ LightDXManager.cpp ] LightDXを管理するクラス
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
#include "004_Component/0040_RenderDX/00400_Light/LightDX.h"
#include "004_Component/0040_RenderDX/00400_Light/LightDXManager.h"

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
std::list<LightDX*> LightDXManager::pLightDXList;

bool LightDXManager::useLightID[MAX_LIGHT_NUM] = {};

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
LightDXManager *LightDXManager::Create()
{
    LightDXManager* pLightDXManager;
    pLightDXManager = new LightDXManager();
    pLightDXManager->Init();

    return pLightDXManager;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void LightDXManager::Init()
{
    // 初期ライトの生成
    GameObject* pLightGameObject = new GameObject("Directional Light");
    pLightGameObject->DontDestroyOnLoad(true);
    pLightGameObject->AddComponent<LightDX>();
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void LightDXManager::Uninit()
{
    ReleaseAll();

    for (int Cnt = 0; Cnt < MAX_LIGHT_NUM; Cnt++)
    {
        useLightID[Cnt] = false;
    }
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void LightDXManager::Update()
{
    //UpdateAll();
}

/*===============================================================================================*
  @Summary: 登録された全てのLightDXを更新する
  @Details: None
 *===============================================================================================*/
void LightDXManager::UpdateAll()
{
    for (auto Iterator = pLightDXList.begin(); Iterator != pLightDXList.end(); ++Iterator)
    {
        (*Iterator)->Update();
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのLightDXを削除する
  @Details: None
 *===============================================================================================*/
void LightDXManager::ReleaseAll()
{
    LightDX* pLightDX;

    for (auto Iterator = pLightDXList.begin(); Iterator != pLightDXList.end();)
    {
        pLightDX = (*Iterator);

        // リストから切り離す
        Iterator = pLightDXList.erase(Iterator);

        // GameObjectの削除
        SafeDeleteUninit(pLightDX);
    }

    pLightDXList.clear();
}

/*===============================================================================================*
  @Summary: LightDXをリストに追加する
  @Details: None
 *===============================================================================================*/
int LightDXManager::LinkList(LightDX* pLightDX)
{
    int LightDXNum;

    for (int Cnt = 0; Cnt < MAX_LIGHT_NUM; Cnt++)
    {
        if (useLightID[Cnt] == false)
        {
            useLightID[Cnt] = true;
            LightDXNum = Cnt;

            pLightDXList.push_back(pLightDX);

            break;
        }
    }

    return LightDXNum;
}

/*===============================================================================================*
  @Summary: LightDXをリストから解除する
  @Details: None
 *===============================================================================================*/
void LightDXManager::UnLinkList(LightDX* pLightDX)
{
    for (auto Iterator = pLightDXList.begin(); Iterator != pLightDXList.end(); ++Iterator)
    {
        if ((*Iterator) == pLightDX)
        {
            // 使用フラグを解放する
            useLightID[pLightDX->GetLightID()] = false;

            // リストから切り離す
            pLightDXList.erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: 対象のLightDXを削除する (リストからも取り除く)
  @Details: 対象のLightDXのUninit()が呼ばれる
 *===============================================================================================*/
void LightDXManager::Release(LightDX* pLightDX)
{
    for (auto Iterator = pLightDXList.begin(); Iterator != pLightDXList.end();)
    {
        if ((*Iterator) == pLightDX)
        {
            // リストから切り離す
            Iterator = pLightDXList.erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pLightDX);

            return;
        }

        ++Iterator;
    }
}

/*===============================================================================================* 
  @Summary: 指定して番号のライトクラスを取得する
  @Details: None
 *===============================================================================================*/
LightDX* LightDXManager::GetLight(int LightID)
{
    for (auto Iterator = pLightDXList.begin(); Iterator != pLightDXList.end();)
    {
        if ((*Iterator)->GetLightID() == LightID)
        {
            return (*Iterator);
        }

        ++Iterator;
    }

    return NULL;
}

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
