/**************************************************************************************************

 @File   : [ RenderGL.cpp ] OpenGLで全てのレンダラーのための一般的な機能を管理するクラス (抽象クラス)
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
#include "004_Component/0041_RenderGL/RenderGL.h"
#include "004_Component/0041_RenderGL/RenderGLManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

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
    enabled = true;
    zDepth  = 1.0f;

    SetLayer(Layer);

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
  @Summary: Renderが持つブレンド設定を行う
  @Details: None
 *===============================================================================================*/
void RenderGL::SetBlending()
{
    // ブレンド Off
    glDisable(GL_BLEND);

    // ブレンド設定
    switch (blendType)
    {
        // ブレンドしない
        case BLENDTYPE_NOTBLEND:
            glDisable(GL_BLEND);
            break;

        // アルファブレンド
        case BLENDTYPE_NORMAL:
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;

        // 加算合成
        case BLENDTYPE_ADD:
            break;

        // 半加算合成
        case BLENDTYPE_ADD_SOFT:
            break;

        // 減算合成
        case BLENDTYPE_SUBTRACT:
            break;

        default:
            break;
    }
}

/*===============================================================================================* 
  @Summary: Renderが持つカリング設定を行う
  @Details: None
 *===============================================================================================*/
void RenderGL::SetCulling()
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
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//