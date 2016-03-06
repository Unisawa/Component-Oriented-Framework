/**************************************************************************************************

 @File   : [ RenderDX.h ] DirectXで全てのレンダラーのための一般的な機能を管理するクラス (抽象クラス)
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
#include "001_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "003_Object/Material.h"
#include "008_Utility/Color.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//-----2DPolygon VertexInformation-----//
typedef struct
{
    Vector3     pos;    // 頂点の位置座標
    COLOR       col;    // 頂点カラー
    D3DXVECTOR2 tex;    // テクスチャ座標

}VERTEX_2D;

//-----3DPolygon VertexInformation-----//
typedef struct
{
    Vector3     pos;    // 頂点の位置座標
    Vector3     nor;    // 法線ベクトル
    COLOR       col;    // 頂点カラー
    D3DXVECTOR2 tex;    // テクスチャ座標

}VERTEX_3D;

//-----VertexFormat-----//
#define FVF_VERTEX_2D (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderDX : public Component
{
public:

    static const enum BLENDTYPE
    {
        BLENDTYPE_NOTBLEND = 0,    // ブレンドしない

        BLENDTYPE_NORMAL,          // アルファブレンド
        BLENDTYPE_ADD,             // 加算合成
        BLENDTYPE_ADD_SOFT,        // 半加算合成
        BLENDTYPE_SUBTRACT,        // 減算合成

        BLENDTYPE_MAX
    };

    static const enum CULLTYPE
    {
        CULLTYPE_NONE = 0,    // カリングしない

        CULLTYPE_CW,          // 表カリング
        CULLTYPE_CCW,         // 裏カリング

        CULLTYPE_MAX
    };

             RenderDX(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer = GameObject::LAYER_ZERO);
    virtual ~RenderDX();

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw()   = 0;

    virtual void SetVertex() = 0;

    static bool ZSortCompareLess(RenderDX* RenderA, RenderDX* RenderB);
    static bool ZSortCompareGreater(RenderDX* RenderA, RenderDX* RenderB);

    static bool SortingOrderCompareLess(RenderDX* RenderA, RenderDX* RenderB);
    static bool SortingOrderCompareGreater(RenderDX* RenderA, RenderDX* RenderB);

    void SetBlending();
    void SetCulling();

    //-----Setter, Getter-----//
    void              SetLayer(GameObject::LAYER value);
    GameObject::LAYER GetLayer() const { return layer; }

    void      SetBlendType(BLENDTYPE value) { blendType = value; }
    BLENDTYPE GetBlendType() const { return blendType; }
    
    void     SetCullType(CULLTYPE value) { cullingType = value; }
    CULLTYPE GetCullType() const { return cullingType; }

    void  SetZDepth(float value) { zDepth = value; }
    float GetZDepth() const { return zDepth; }

    void  SetSortingOrder(float value) { sortingOrder = value; }
    float GetSortingOrder() const { return sortingOrder; }

    void     SetTexture(std::string value);
    void     SetTexture(Texture* value);
    Texture* GetTexture() { return material.mainTexture; }

    void     SetTextureID(unsigned int value);
    int      GetTextureID() const { return material.mainTextureID; }

    bool enabled;    // True時のみ描画を行う

    Material          material;       // マテリアル情報

private:
    GameObject::LAYER layer;          // 描画順
    BLENDTYPE         blendType;      // 描画時のブレンド設定
    CULLTYPE          cullingType;    // 描画時のカリング設定

    float zDepth;                     // カメラからオブジェクトまでの距離 (Zソート時に利用)
    float sortingOrder;               // 同じレイヤー時の描画順番の制御に使用する
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//