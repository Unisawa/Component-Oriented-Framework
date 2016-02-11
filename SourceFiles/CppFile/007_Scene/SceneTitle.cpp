/**************************************************************************************************

 @File   : [ SceneTitle.cpp ] 
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
#include "004_Component/SceneTitle.h"

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
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
SceneTitle::SceneTitle()
{

}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
SceneTitle::~SceneTitle()
{

}

/*===============================================================================================* 
  @Summary: ��������
  @Details: None
 *===============================================================================================*/
SceneTitle *SceneTitle::Create()
{
    SceneTitle* pSceneTitle;
    pSceneTitle = new SceneTitle();
    pSceneTitle->Init();

    return pSceneTitle;
}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void SceneTitle::Init()
{

}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void SceneTitle::Uninit()
{

}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void SceneTitle::Update()
{

}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void SceneTitle::Draw()
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