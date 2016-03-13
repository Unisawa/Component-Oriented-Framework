/**************************************************************************************************

 @File   : [ RenderDX.cpp ] DirectXで全てのレンダラーのための一般的な機能を管理するクラス (抽象クラス)
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
#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0040_RenderDX/00403_Texture/TextureDXManager.h"

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
//***********************************************************************************************//

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
RenderDX::RenderDX(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer) : Component(pObject, RENDERER, ComponentName)
{
    enabled      = true;
    zDepth       = 1.0f;
    sortingOrder = 0.0f;
    layer        = Layer;
    transform    = pObject->transform;
    isLighiting  = true;

    blendType    = BLENDTYPE::BLENDTYPE_NORMAL;
    cullingType  = CULLTYPE::CULLTYPE_CCW;

    RenderDXManager::LinkList(this, Layer);
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
RenderDX::~RenderDX()
{

}

/*===============================================================================================* 
  @Summary: ZDepthの値を参考にソートする Bに対してAの方が小さいか
  @Details: None
 *===============================================================================================*/
bool RenderDX::ZSortCompareLess(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetZDepth() < RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: ZDepthの値を参考にソートする Bに対してAの方が大きいか
  @Details: None
 *===============================================================================================*/
bool RenderDX::ZSortCompareGreater(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetZDepth() > RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: sortingOrderの値を参考にソートする Bに対してAの方が小さいか
  @Details: None
 *===============================================================================================*/
bool RenderDX::SortingOrderCompareLess(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetSortingOrder() < RenderB->GetSortingOrder();
}

/*===============================================================================================* 
  @Summary: sortingOrderの値を参考にソートする Bに対してAの方が大きいか
  @Details: None
 *===============================================================================================*/
bool RenderDX::SortingOrderCompareGreater(RenderDX* RenderA, RenderDX* RenderB)
{
    return RenderA->GetSortingOrder() > RenderB->GetSortingOrder();
}

/*===============================================================================================* 
  @Summary: Renderingの設定を行う
  @Details: 描画する前に必ず呼ぶ関数
 *===============================================================================================*/
void RenderDX::SetUpRendering()
{
    // 描画設定
    SetUpBlending();
    SetUpCulling();
    SetUpMaterial();

    // ライト設定
    if (isLighiting)
    {
        RenderDXManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
    }
    else
    {
        RenderDXManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
    }
}

/*===============================================================================================* 
  @Summary: Renderingの設定を解除する
  @Details: 描画し終わったら必ず呼ぶ関数
 *===============================================================================================*/
void RenderDX::ResetRendering()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // テクスチャのリセット
    pDevice->SetTexture(0, TextureDXManager::GetTexture(NULL));
}

/*===============================================================================================* 
  @Summary: Renderが持つブレンド設定を行う
  @Details: None
 *===============================================================================================*/
void RenderDX::SetUpBlending()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // ブレンドモードのリセット (アルファブレンドを基本とする)
    pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
    pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // ブレンド設定
    switch (blendType)
    {
        // ブレンドしない
        case BLENDTYPE_NOTBLEND:
            pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
            break;

        // アルファブレンド
        case BLENDTYPE_NORMAL:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
            break;

        // 加算合成 (α無)
        case BLENDTYPE_ADD:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        // 加算合成 (α有)
        case BLENDTYPE_ADD_SOFT:
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        // 減算合成
        case BLENDTYPE_SUBTRACT:
            pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
            pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
            pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Renderが持つカリング設定を行う
  @Details: None
 *===============================================================================================*/
void RenderDX::SetUpCulling()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // カリングのリセット (裏カリングを基本とする)
    pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    // カリング設定
    switch (cullingType)
    {
        // カリングしない
        case CULLTYPE_NONE:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            break;

        // 表カリング
        case CULLTYPE_CW:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
            break;

        // 裏カリング
        case CULLTYPE_CCW:
            pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Renderが持つマテリアルの設定を行う
  @Details: None
 *===============================================================================================*/
void RenderDX::SetUpMaterial()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // テクスチャのセット
    pDevice->SetTexture(0, TextureDXManager::GetTexture(material.mainTextureID));
}

/*===============================================================================================* 
  @Summary: Layer (描画順) を変更する
  @Details: None
 *===============================================================================================*/
void RenderDX::SetLayer(GameObject::LAYER value)
{
    if (layer == value) return;

    RenderDXManager::UnLinkList(this);
    layer = value;
    RenderDXManager::LinkList(this, value);
}

/*===============================================================================================* 
  @Summary: 指定したテクスチャ名のテクスチャを設定する
  @Details: 未読み込みの場合は読み込む
 *===============================================================================================*/
void RenderDX::SetTexture(std::string value)
{
    material.mainTexture = TextureDXManager::Load(value);

    if (material.mainTexture != NULL)
    {
        material.mainTextureID = material.mainTexture->textureID;
    }
}

/*===============================================================================================* 
  @Summary: 指定したテクスチャクラスを直接設定する
  @Details: None
 *===============================================================================================*/
void RenderDX::SetTexture(Texture* value)
{
    material.mainTexture   = value;
    material.mainTextureID = value->textureID;

    value->repeatedNum++;    // このテクスチャを使用している数が増えたため増加させる
}

/*===============================================================================================* 
  @Summary: 指定したテクスチャID(Hash値)を直接設定する
  @Details: None
 *===============================================================================================*/
void RenderDX::SetTextureID(unsigned int value)
{
    material.mainTextureID = value;
}

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
