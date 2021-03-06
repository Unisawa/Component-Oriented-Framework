/**************************************************************************************************

 @File   : [ Component.cpp ] GameObject にアタッチされる全てに対するベースのクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "004_Component/Component.h"

//-----Object-----//
#include "004_Component/0042_GameObject/GameObject.h"

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
Component::Component(GameObject* pObject, COMPONENTTYPE Type, std::string ComponentName)
{
    gameObject    = pObject;

    componentType = Type;
    componentName = ComponentName;
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
Component::~Component()
{

}

/*===============================================================================================* 
  @Summary: Componentの削除
  @Details: None
 *===============================================================================================*/
void Component::Destroy(float time)
{
    gameObject->Destroy(this, time);
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
