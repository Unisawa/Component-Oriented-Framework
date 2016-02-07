/**************************************************************************************************

 @File   : [ Render2DDX.cpp ] 
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Object-----//
#include "004_Component/Render2DDX.h"

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
Render2DDX::Render2DDX()
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
Render2DDX::~Render2DDX()
{

}

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
Render2DDX *Render2DDX::Create()
{
    Render2DDX* pRender2DDX;
    pRender2DDX = new Render2DDX();
    pRender2DDX->Init();

    return pRender2DDX;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void Render2DDX::Init()
{

}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Render2DDX::Uninit()
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Render2DDX::Update()
{

}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void Render2DDX::Draw()
{

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