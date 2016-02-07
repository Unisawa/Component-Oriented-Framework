/**************************************************************************************************

 @File   : [ RenderDX.h ] 全てのレンダラーのための一般的な機能を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERDX_H_
#define _RENDERDX_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/GameObject.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//-----2DPolygon VertexInformation-----//
typedef struct
{
    D3DXVECTOR3 pos;    // 頂点の位置座標
    float       rhw;    // 3Dにおける2Dテクスチャのゆがみ補正のデータ パースペクティブコレクト
    D3DCOLOR    col;    // 頂点カラー
    D3DXVECTOR2 tex;    // テクスチャ座標

}VERTEX_2D;

//-----3DPolygon VertexInformation-----//
typedef struct
{
    D3DXVECTOR3 pos;    // 頂点の位置座標
    D3DXVECTOR3 nor;    // 法線ベクトル
    D3DCOLOR    col;    // 頂点カラー
    D3DXVECTOR2 tex;    // テクスチャ座標

}VERTEX_3D;

//-----VertexFormat-----//
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderDX : public Component
{
public:
             RenderDX(GameObject::LAYER Layer = GameObject::LAYER_ZERO);
    virtual ~RenderDX();

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    static bool ZSortCompareLess(RenderDX* RenderA, RenderDX* RenderB);
    static bool ZSortCompareGreater(RenderDX* RenderA, RenderDX* RenderB);

    //-----Setter, Getter-----//
    void              SetLayer(GameObject::LAYER value) { layer = value; }
    GameObject::LAYER GetLayer() const { return layer; }

    float GetZDepth() const { return zDepth; }

    bool enabled;    // True時のみ描画を行う

private:
    GameObject::LAYER layer;    // 描画順

    float zDepth;    // カメラからオブジェクトまでの距離 (Zソート時に利用)
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//