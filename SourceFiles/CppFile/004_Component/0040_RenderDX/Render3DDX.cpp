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

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
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
    size        = Vector3(10.0f, 0.0f, 10.0f);

    vertexColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    textureUV   = D3DXVECTOR2(0.0f, 0.0f);
    textureID   = -1;

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
    SetVertex();
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void Render3DDX::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    // 描画設定
    SetBlending();
    SetCulling();

    // 頂点バッファの描画設定
    pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(VERTEX_3D));
    pDevice->SetFVF(FVF_VERTEX_3D);

    // テクスチャの読み込み ポリゴンの描画
    pDevice->SetTexture(0, NULL);
    //pDevice->SetTexture(0, TextureManager::GetTexture(TextureID));
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
    pVtx[0].nor = Vector3(0.0f, 1.0f, 0.0f);
    pVtx[1].nor = Vector3(0.0f, 1.0f, 0.0f);
    pVtx[2].nor = Vector3(0.0f, 1.0f, 0.0f);
    pVtx[3].nor = Vector3(0.0f, 1.0f, 0.0f);

    // ポリゴンのカラー情報
    pVtx[0].col = vertexColor;
    pVtx[1].col = vertexColor;
    pVtx[2].col = vertexColor;
    pVtx[3].col = vertexColor;

    // ポリゴンのテクスチャ座標
    pVtx[0].tex = D3DXVECTOR2(textureUV.x + 0.0f, textureUV.y + 0.0f);
    pVtx[1].tex = D3DXVECTOR2(textureUV.x + 1.0f, textureUV.y + 0.0f);
    pVtx[2].tex = D3DXVECTOR2(textureUV.x + 0.0f, textureUV.y + 1.0f);
    pVtx[3].tex = D3DXVECTOR2(textureUV.x + 1.0f, textureUV.y + 1.0f);

    // 頂点バッファ領域のアンロック
    pVertexBuffer->Unlock();
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