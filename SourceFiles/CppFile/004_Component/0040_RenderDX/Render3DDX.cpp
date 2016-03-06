/**************************************************************************************************

 @File   : [ Render3DDX.cpp ] DirectXで3D四角形ポリゴンを描画するRenderクラス
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
#include "004_Component/0040_RenderDX/Render3DDX.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0040_RenderDX/00403_Texture/TextureDXManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

const std::string Render3DDX::className = "Render3DDX";

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
Render3DDX::Render3DDX(GameObject* pObject, GameObject::LAYER Layer) : RenderDX(pObject, className, Layer)
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
Render3DDX::~Render3DDX()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void Render3DDX::Init()
{
    size = Vector3(1.0f, 0.0f, 1.0f);

    // 頂点バッファーの確保
    RenderDXManager::GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);

    SetVertex();
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Render3DDX::Uninit()
{
    RenderDXManager::UnLinkList(this);

    SafeRelease(pVertexBuffer);
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Render3DDX::Update()
{

}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void Render3DDX::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // ワールド行列生成
    transform->CreateWorldMatrix();
    pDevice->SetTransform(D3DTS_WORLD, &transform->GetWorldMatrix());

    // 描画設定
    SetBlending();
    SetCulling();

    // 頂点バッファの描画設定
    pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
    pDevice->SetFVF(FVF_VERTEX_3D);

    // テクスチャの読み込み ポリゴンの描画
    pDevice->SetTexture(0, TextureDXManager::GetTexture(material.mainTextureID));
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    // テクスチャリセット
    pDevice->SetTexture(0, NULL);
}

/*===============================================================================================* 
  @Summary: 頂点情報の更新
  @Details: None
 *===============================================================================================*/
void Render3DDX::SetVertex()
{
    VERTEX_3D* pVtx;
    Vector3 Position = this->gameObject->transform->GetPosition();
    Vector3 Scale    = this->gameObject->transform->GetScale();

    // 頂点バッファ領域のロック
    pVertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

    // ポリゴンの位置座標
    pVtx[0].pos.x = -size.x;
    pVtx[0].pos.y =  0.0f;
    pVtx[0].pos.z =  size.z;

    pVtx[1].pos.x =  size.x;
    pVtx[1].pos.y =  0.0f;
    pVtx[1].pos.z =  size.z;

    pVtx[2].pos.x = -size.x;
    pVtx[2].pos.y =  0.0f;
    pVtx[2].pos.z = -size.z;

    pVtx[3].pos.x =  size.x;
    pVtx[3].pos.y =  0.0f;
    pVtx[3].pos.z = -size.z;

    // ポリゴンの同次座標--固定--
    pVtx[0].nor = Vector3::up;
    pVtx[1].nor = Vector3::up;
    pVtx[2].nor = Vector3::up;
    pVtx[3].nor = Vector3::up;

    // ポリゴンのカラー情報
    pVtx[0].col = material.color.Trans();
    pVtx[1].col = material.color.Trans();
    pVtx[2].col = material.color.Trans();
    pVtx[3].col = material.color.Trans();

    // ポリゴンのテクスチャ座標
    pVtx[0].tex = D3DXVECTOR2(material.mainTextureOffset.x                              , material.mainTextureOffset.y);
    pVtx[1].tex = D3DXVECTOR2(material.mainTextureOffset.x + material.mainTextureScale.x, material.mainTextureOffset.y);
    pVtx[2].tex = D3DXVECTOR2(material.mainTextureOffset.x                              , material.mainTextureOffset.y + material.mainTextureScale.y);
    pVtx[3].tex = D3DXVECTOR2(material.mainTextureOffset.x + material.mainTextureScale.x, material.mainTextureOffset.y + material.mainTextureScale.y);

    // 頂点バッファ領域のアンロック
    pVertexBuffer->Unlock();
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//