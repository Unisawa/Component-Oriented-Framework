/**************************************************************************************************

 @File   : [ RenderGL.cpp ] OpenGLで全てのレンダラーのための一般的な機能を管理するクラス (抽象クラス)
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0041_RenderGL/RenderGL.h"
#include "004_Component/0041_RenderGL/RenderGLManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_OPENGL

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
RenderGL::RenderGL(GameObject* pObject, std::string ComponentName, GameObject::LAYER Layer) : Component(pObject, RENDERER, ComponentName)
{
    enabled      = true;
    zDepth       = 1.0f;
    sortingOrder = 0.0f;
    layer        = Layer;
    transform    = pObject->transform;

    blendType    = BLENDTYPE::BLENDTYPE_NORMAL;
    cullingType  = CULLTYPE::CULLTYPE_CCW;

    RenderGLManager::LinkList(this, Layer);
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
RenderGL::~RenderGL()
{

}

/*===============================================================================================* 
  @Summary: ZDepthの値を参考にソートする Bに対してAの方が小さいか
  @Details: None
 *===============================================================================================*/
bool RenderGL::ZSortCompareLess(RenderGL* RenderA, RenderGL* RenderB)
{
    return RenderA->GetZDepth() < RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: ZDepthの値を参考にソートする Bに対してAの方が大きいか
  @Details: None
 *===============================================================================================*/
bool RenderGL::ZSortCompareGreater(RenderGL* RenderA, RenderGL* RenderB)
{
    return RenderA->GetZDepth() > RenderB->GetZDepth();
}

/*===============================================================================================* 
  @Summary: sortingOrderの値を参考にソートする Bに対してAの方が小さいか
  @Details: None
 *===============================================================================================*/
bool RenderGL::SortingOrderCompareLess(RenderGL* RenderA, RenderGL* RenderB)
{
    return RenderA->GetSortingOrder() < RenderB->GetSortingOrder();
}

/*===============================================================================================* 
  @Summary: sortingOrderの値を参考にソートする Bに対してAの方が大きいか
  @Details: None
 *===============================================================================================*/
bool RenderGL::SortingOrderCompareGreater(RenderGL* RenderA, RenderGL* RenderB)
{
    return RenderA->GetSortingOrder() > RenderB->GetSortingOrder();
}

/*===============================================================================================* 
  @Summary: Renderが持つブレンド設定を行う
  @Details: None
 *===============================================================================================*/
void RenderGL::SetUpBlending()
{
    // ブレンドモードのリセット (アルファブレンドを基本とする)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ブレンド設定
    switch (blendType)
    {
        // ブレンドしない
        case BLENDTYPE_NOTBLEND:
            glDisable(GL_BLEND);
            break;

        // アルファブレンド
        case BLENDTYPE_NORMAL:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;

        // 加算合成 (α無)
        case BLENDTYPE_ADD:
            glBlendFunc(GL_ONE, GL_ONE);
            break;

        // 加算合成 (α有)
        case BLENDTYPE_ADD_SOFT:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Renderが持つカリング設定を行う
  @Details: None
 *===============================================================================================*/
void RenderGL::SetUpCulling()
{
    //LPDIRECT3DDEVICE9 pDevice = RenderDXManager::GetDevice();

    //// カリングのリセット (裏カリングを基本とする)
    //pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    //// カリング設定
    //switch (cullingType)
    //{
    //    // カリングしない
    //    case CULLTYPE_NONE:
    //        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    //        break;

    //    // 表カリング
    //    case CULLTYPE_CW:
    //        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
    //        break;

    //    // 裏カリング
    //    case CULLTYPE_CCW:
    //        pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //        break;

    //    default:
    //        break;
    //}
}

/*===============================================================================================* 
  @Summary: Layer (描画順) を変更する
  @Details: None
 *===============================================================================================*/
void RenderGL::SetLayer(GameObject::LAYER value)
{
    if (layer == value) return;

    RenderGLManager::UnLinkList(this);
    layer = value;
    RenderGLManager::LinkList(this, value);
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
