/**************************************************************************************************

 @File   : [ RenderGL.h ] OpenGLで全てのレンダラーのための一般的な機能を管理するクラス (抽象クラス)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _RENDERGL_H_
#define _RENDERGL_H_

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
#ifdef USE_OPENGL

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class RenderGL : public Component
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

             RenderGL(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer = GameObject::LAYER_ZERO);
    virtual ~RenderGL();

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw()   = 0;
    
    static bool ZSortCompareLess(RenderGL* RenderA, RenderGL* RenderB);
    static bool ZSortCompareGreater(RenderGL* RenderA, RenderGL* RenderB);

    static bool SortingOrderCompareLess(RenderGL* RenderA, RenderGL* RenderB);
    static bool SortingOrderCompareGreater(RenderGL* RenderA, RenderGL* RenderB);

    void SetUpBlending();
    void SetUpCulling();

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