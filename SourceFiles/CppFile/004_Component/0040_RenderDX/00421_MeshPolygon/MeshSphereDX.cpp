/**************************************************************************************************

 @File   : [ MeshSphereDX.cpp ] 球状のメッシュを生成するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/00420_Mesh/MeshDX.h"
#include "004_Component/0040_RenderDX/00420_Mesh/MeshFilterDX.h"
#include "004_Component/0040_RenderDX/00420_Mesh/MeshRenderDX.h"
#include "004_Component/0040_RenderDX/00421_MeshPolygon/MeshSphereDX.h"
#include "008_Utility/Vector3.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

const std::string MeshSphereDX::className = "MeshSphereDX";

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
MeshSphereDX::MeshSphereDX(GameObject* pObject) : MeshFilterDX(pObject, className)
{
    radius          = 1.0f;
    normalDirection = -1.0f;
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
MeshSphereDX::~MeshSphereDX()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void MeshSphereDX::Init()
{
    pMesh->ResetBufer(10, 10);
    SetUpVertex();

    pMeshRender->SetMesh(pMesh);
    pMeshRender->SetCullType(RenderDX::CULLTYPE::CULLTYPE_CW);
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void MeshSphereDX::Uninit()
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void MeshSphereDX::Update()
{

}

/*===============================================================================================* 
  @Summary: 球状のメッシュを設定する
  @Details: None
 *===============================================================================================*/
void MeshSphereDX::SetUpVertex()
{
    // デバイスオブジェクトの取得
    LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    VERTEX_3D* pVtx;    // 座標ポインタ
    WORD*      pIdx;    // インデックスポインタ

    // 頂点バッファ領域のロック
    pMesh->pVertexBuffer->Lock(0, 0, (void**)&pVtx, 0);

    int   nCnt = 0;    // 現在の頂点番号

    float RadX       = D3DX_PI * 2;
    float RadRadtioX = D3DX_PI * 2 / pMesh->divisionX;

    float RadY       = D3DX_PI;
    float RadRadtioY = D3DX_PI / pMesh->divisionY;

    // 頂点座標を球体状に設定する
    for (int nDivZ = 0; nDivZ <= pMesh->divisionY; nDivZ++)
    {
        RadX = 0.0f;

        for (int nDivX = 0; nDivX <= pMesh->divisionX; nDivX++)
        {
            // 初期座標設定
            pVtx[nCnt].pos.x = sinf(RadX) * sinf(RadY) * radius;
            pVtx[nCnt].pos.y = radius     * cosf(D3DX_PI + RadY);
            pVtx[nCnt].pos.z = cosf(RadX) * sinf(RadY) * radius;

            // 法線の向き
            pVtx[nCnt].nor = Vector3::Vec3Normalize(&pVtx[nCnt].pos) * normalDirection;
            //Debug::Log("(%f, %f, %f)", pVtx[nCnt].nor.x, pVtx[nCnt].nor.y, pVtx[nCnt].nor.z);

            // 色情報
            pVtx[nCnt].col = pMeshRender->material.color.Trans();

            // テクスチャ座標
            pVtx[nCnt].tex = Vector2((float)(1.0f / pMesh->divisionX) * nDivX, (float)(1.0f / pMesh->divisionY) * nDivZ);

            RadX += RadRadtioX;
            nCnt++;
        }

        RadY -= RadRadtioY;
    }

    // 頂点バッファ領域のアンロック
    pMesh->pVertexBuffer->Unlock();

    // インデックスバッファ領域のロック
    pMesh->pIndexBuffer->Lock(0, 0, (void**)&pIdx, 0);

    nCnt = 0;    // 現在の頂点番号

    // インデックスの設定 (描画するポリゴンの頂点の順番 -2頂点を同時に設定していく- )
    for (int nDivZ = 0; nDivZ < pMesh->divisionY; nDivZ++)
    {
        for (int nDivX = 0; nDivX <= pMesh->divisionX; nDivX++)
        {
            // インデックス情報
            pIdx[nCnt + 0] = nDivX + (pMesh->divisionX + 1) * (nDivZ + 1);
            pIdx[nCnt + 1] = nDivX + (pMesh->divisionX + 1) * nDivZ;

            // 同じ場所に頂点を重ねる (折り返し地点)
            if (((nCnt + 1) == (pMesh->divisionX * 2 + 1) + (6 + (pMesh->divisionX - 1) * 2) * nDivZ) &&
                ((nCnt + 1) != pMesh->vertexIndexNum - 1))
            {
                nCnt += 2;

                pIdx[nCnt + 0] = (pMesh->divisionX + 1) * nDivZ + nDivX;    // 折り返し地点
                pIdx[nCnt + 1] = (pMesh->divisionX + 1) * (nDivZ + 2);      // 折り返し先の地点
            }

            nCnt += 2;    // 頂点番号を進める
        }
    }

    pMesh->pIndexBuffer->Unlock();    // インデックスバッファ領域のアンロック
}

/*===============================================================================================* 
  @Summary: 指定した情報でメッシュを再生成する
  @Details: None
 *===============================================================================================*/
void MeshSphereDX::SetUpSphere(int DivX, int DivY, float Radius)
{
    radius = Radius;

    pMesh->ResetBufer(DivX, DivY);
    SetUpVertex();
}

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
