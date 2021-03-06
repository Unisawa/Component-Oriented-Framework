/**************************************************************************************************

 @File   : [ FadeDX.cpp ] 画面全体の照度を変化させるフェードクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"
#include "002_Constant/Constant.h"

//-----Object-----//
#include "007_Scene/0070_Fade/FadeDX.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0040_RenderDX/00410_Base/Render2DDX.h"

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
const std::string FadeDX::className = "FadeDX";

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
FadeDX::FadeDX(GameObject* pObject) : Fade(pObject, className)
{
    fadeTime  = 20;
    fadeCount = 0;

    fadeState = FADE::NONE;
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
FadeDX::~FadeDX()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void FadeDX::Init()
{
    fadeState = FADE::IDOL;

    // 画面遷移中の処理なので画面遷移しても消さない
    gameObject->DontDestroyOnLoad(true);

    // FadeDX用 2Dポリゴン追加
    pRender2D = gameObject->AddComponent<Render2DDX>();
    pRender2D->SetSize(Vector2(Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT));
    pRender2D->SetLayer(GameObject::LAYER::OBJECT2D_TRANSLUCENT_TWO);
    pRender2D->SetColor(0.0f, 0.0f, 0.0f, 0.0f);
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void FadeDX::Uninit()
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void FadeDX::Update()
{
    UpdateFadeIn();
    UpdateFadeOut();
}

/*===============================================================================================* 
  @Summary: FadeIn中の処理
  @Details: None
 *===============================================================================================*/
void FadeDX::UpdateFadeIn()
{
    if (fadeState != FADE::FADEIN) return;

    // α計算
    Color color = pRender2D->GetColor();
    color.a = 1.0f * (1 - ((float)fadeCount / fadeTime));

    // 頂点情報の更新
    pRender2D->SetColor(color);

    // フェードが終われば、フェード実行状態を解除
    if (fadeTime < ++fadeCount)
    {
        fadeCount = fadeTime;
        fadeState = FADE::IDOL;
    }
}

/*===============================================================================================* 
  @Summary: FadeOut中の処理
  @Details: None
 *===============================================================================================*/
void FadeDX::UpdateFadeOut()
{
    if (fadeState != FADE::FADEOUT) return;

    // α計算
    Color color = pRender2D->GetColor();
    color.a     = 1.0f * ((float)fadeCount / fadeTime);

    // 頂点情報の更新
    pRender2D->SetColor(color);

    // フェードが終われば、フェード実行状態を解除
    if (fadeTime < ++fadeCount)
    {
        fadeCount = fadeTime;
        fadeState = FADE::IDOL;
    }
}

/*===============================================================================================* 
  @Summary: FadeDXする色を設定する
  @Details: α情報をフェード時に操作するので今は設定できないようにしている
 *===============================================================================================*/
void FadeDX::SetColor(Color value)
{
    pRender2D->material.color.r = value.r;
    pRender2D->material.color.g = value.g;
    pRender2D->material.color.b = value.b;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
