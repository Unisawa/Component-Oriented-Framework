﻿/**************************************************************************************************

 @File   : [ MeshDX.cpp ] スクリプトからメッシュを作成または変更できるようにするクラス
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
#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/00420_Mesh/MeshDX.h"

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
MeshDX::MeshDX() : Object()
{
    pVertexBuffer = NULL;
    pIndexBuffer  = NULL;

    vertexNum      = 0;
    vertexIndexNum = 0;

    divisionX = 1;
    divisionY = 1;

    CreateVertexBuffer();
    CreateIndexBuffer();
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
MeshDX::~MeshDX()
{
    // バッファの削除
    SafeRelease(pVertexBuffer);
    SafeRelease(pIndexBuffer);
}

/*===============================================================================================* 
  @Summary: 頂点バッファの生成
  @Details: None
 *===============================================================================================*/
void MeshDX::CreateVertexBuffer()
{
    // 頂点数の計算
    vertexNum = (divisionX + 1) * (divisionY + 1);

    SafeRelease(pVertexBuffer);
    RenderDXManager::GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * vertexNum, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &pVertexBuffer, NULL);
}

/*===============================================================================================* 
  @Summary: インデックスバッファの生成
  @Details: None
 *===============================================================================================*/
void MeshDX::CreateIndexBuffer()
{
    // インテックス数の計算
    vertexIndexNum = (divisionX + 1) * (divisionY * 2) + (2 * divisionY - 2);

    SafeRelease(pIndexBuffer);
    RenderDXManager::GetDevice()->CreateIndexBuffer(sizeof(WORD) * vertexIndexNum, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
}

/*===============================================================================================* 
  @Summary: 分割数を変更してバッファを作り直す
  @Details: None
 *===============================================================================================*/
void MeshDX::ResetBufer(int DivX, int DivY)
{
    divisionX = DivX;
    divisionY = DivY;

    CreateVertexBuffer();
    CreateIndexBuffer();
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

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
