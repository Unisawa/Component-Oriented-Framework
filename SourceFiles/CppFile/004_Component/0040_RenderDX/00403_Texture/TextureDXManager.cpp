/**************************************************************************************************

 @File   : [ TextureDXManager.cpp ] TextureDXを管理するクラス
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
#include "004_Component/0040_RenderDX/00403_Texture/TextureDX.h"
#include "004_Component/0040_RenderDX/00403_Texture/TextureDXManager.h"
#include "008_Utility/Hash.h"

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
std::list<TextureDX*> TextureDXManager::pTextureDXList;

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
TextureDXManager *TextureDXManager::Create()
{
    TextureDXManager* pTextureDXManager;
    pTextureDXManager = new TextureDXManager();
    pTextureDXManager->Init();

    return pTextureDXManager;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void TextureDXManager::Init()
{

}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void TextureDXManager::Uninit()
{
    ReleaseAll();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void TextureDXManager::Update()
{

}

/*===============================================================================================* 
  @Summary: 既に読み込まれているか確認する
  @Details: None
 *===============================================================================================*/
TextureDX* TextureDXManager::CheckLoaded(const std::string TextureName)
{
    // ロード済みのテクスチャかどうか、ファイル名から生成したハッシュ値で判定する
    unsigned int HashNumber = Hash::CRC32Hash(TextureName.c_str());

    for (auto Iterator = pTextureDXList.begin(); Iterator != pTextureDXList.end(); ++Iterator)
    {
        if ((*Iterator)->textureID == HashNumber)
        {
            //Debug::Log("[ Loaded Texture Hash: %u ] %s", HashNumber, TextureName.c_str());

            (*Iterator)->repeatedNum++;

            return (*Iterator);
        }
    }

    // 未読み込み
    return NULL;
}

/*===============================================================================================* 
  @Summary: テクスチャを読み込み、テクスチャ識別番号を返す
  @Details: .bmp、.dds、.dib、.jpg、.png、.tga の読み込みに対応
 *===============================================================================================*/
TextureDX* TextureDXManager::Load(const std::string TextureName)
{
    std::string FilePath = Constant::PATH_RESOURCE + Constant::PATH_TEXTURE + TextureName;

    TextureDX* pCheckTexture = CheckLoaded(FilePath.c_str());

    // 読み込み済みテクスチャならそれを返す
    if (pCheckTexture != NULL) return pCheckTexture;

    // テクスチャのロードを開始する
    LPDIRECT3DDEVICE9  pDevice = RenderDXManager::GetDevice();
    LPDIRECT3DTEXTURE9 pTempTexture;

    if (D3DXCreateTextureFromFile(pDevice, FilePath.c_str(), &pTempTexture) != D3D_OK)
    {
        Debug::Log("[ Not Find Texture ] : %s", FilePath.c_str());

        return NULL;    // テクスチャ読み込みエラー (FileName間違えの可能性有)
    }

    // ロード完了、リストに追加する
    TextureDX* pTexture = new TextureDX();
    pTexture->SetName(TextureName);
    pTexture->pTexture  = pTempTexture;
    pTexture->textureID = Hash::CRC32Hash(FilePath);

    LinkList(pTexture);

    return pTexture;
}

/*===============================================================================================*
  @Summary: 重複読み込みカウント減らし、一枚も使っていなければ削除する
  @Details: None
*===============================================================================================*/
void TextureDXManager::Delete(unsigned int TextureID)
{
    for (auto Iterator = pTextureDXList.begin(); Iterator != pTextureDXList.end();)
    {
        if ((*Iterator)->textureID == TextureID)
        {
            (*Iterator)->repeatedNum--;

            // 重複読み込み数が0の場合のみ削除する
            if ((*Iterator)->repeatedNum  == 0)
            {
                TextureDX* pTexture = (*Iterator);

                Debug::Log("[   Delete Texture ] Name: %s", (*Iterator)->GetName());
 
                // リストから削除、テクスチャ削除
                Iterator = pTextureDXList.erase(Iterator);

                SafeDeleteUninit(pTexture);

                return;
            }
        }

        ++Iterator;
    }
}

/*===============================================================================================* 
  @Summary: テクスチャIDからテクスチャデータを取得する
  @Details: None
 *===============================================================================================*/
LPDIRECT3DTEXTURE9 TextureDXManager::GetTexture(unsigned int TextureID)
{
    for (auto Iterator = pTextureDXList.begin(); Iterator != pTextureDXList.end();)
    {
        if ((*Iterator)->textureID == TextureID)
        {
            return (*Iterator)->pTexture;
        }

        ++Iterator;
    }

    return NULL;
}

/*===============================================================================================*
  @Summary: 登録された全てのTextureDXを削除する
  @Details: None
 *===============================================================================================*/
void TextureDXManager::ReleaseAll()
{
    TextureDX* pTextureDX;

    for (auto Iterator = pTextureDXList.begin(); Iterator != pTextureDXList.end();)
    {
        pTextureDX = (*Iterator);

        // リストから切り離す
        Iterator = pTextureDXList.erase(Iterator);

        // GameObjectの削除
        SafeDeleteUninit(pTextureDX);
    }

    pTextureDXList.clear();
}

/*===============================================================================================*
  @Summary: TextureDXをリストに追加する
  @Details: None
 *===============================================================================================*/
void TextureDXManager::LinkList(TextureDX* pTextureDX)
{
    pTextureDXList.push_back(pTextureDX);
}

/*===============================================================================================*
  @Summary: TextureDXをリストから解除する
  @Details: None
 *===============================================================================================*/
void TextureDXManager::UnLinkList(TextureDX* pTextureDX)
{
    for (auto Iterator = pTextureDXList.begin(); Iterator != pTextureDXList.end(); ++Iterator)
    {
        if ((*Iterator) == pTextureDX)
        {
            // リストから切り離す
            pTextureDXList.erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: 対象のTextureDXを削除する (リストからも取り除く)
  @Details: 対象のTextureDXのUninit()が呼ばれる
 *===============================================================================================*/
void TextureDXManager::Release(TextureDX* pTextureDX)
{
    for (auto Iterator = pTextureDXList.begin(); Iterator != pTextureDXList.end();)
    {
        if ((*Iterator) == pTextureDX)
        {
            // リストから切り離す
            Iterator = pTextureDXList.erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pTextureDX);

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
