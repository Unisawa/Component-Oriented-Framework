/**************************************************************************************************

 @File   : [ Render2DGL.cpp ] OpenGL��2D�l�p�`�|���S����`�悷��Render�N���X
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"
#include "001_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0041_RenderGL/RenderGL.h"
#include "004_Component/0041_RenderGL/Render2DGL.h"
#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define COMPONENT_NAME "Render2DGL"

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*=================================================================================================
  @Summary: �R���X�g���N�^
  @Details: None
=================================================================================================*/
Render2DGL::Render2DGL(GameObject* pObject, GameObject::LAYER Layer) : RenderGL(pObject, COMPONENT_NAME, Layer)
{

}

/*===============================================================================================* 
  @Summary: �f�X�g���N�^
  @Details: None
 *===============================================================================================*/
Render2DGL::~Render2DGL()
{

}

/*===============================================================================================* 
  @Summary: ����������
  @Details: None
 *===============================================================================================*/
void Render2DGL::Init()
{
    textureID = -1;
}

/*===============================================================================================* 
  @Summary: �I������
  @Details: None
 *===============================================================================================*/
void Render2DGL::Uninit()
{

}

/*===============================================================================================* 
  @Summary: �X�V����
  @Details: None
 *===============================================================================================*/
void Render2DGL::Update()
{

}

/*===============================================================================================* 
  @Summary: �`�揈��
  @Details: None
 *===============================================================================================*/
void Render2DGL::Draw()
{
    Transform* pTransform = this->gameObject->GetTransform();

    float x = pTransform->GetPosition().x;
    float y = pTransform->GetPosition().y;

    float SizeX = pTransform->GetScale().x;
    float SizeY = pTransform->GetScale().y;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ���ˉe�s��
    glOrtho(0.0f, Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT, 0.0f, 0.0f, 10000.0f);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 2D�`��ݒ�
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    // �`��ݒ�
    SetBlending();
    SetCulling();

    // �e�N�X�`���Z�b�g
    //glBindTexture(GL_TEXTURE_2D,textureID);

    // �`��J�n
    glBegin(GL_TRIANGLE_STRIP);

    // ����
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x - SizeX * 0.5f,
               y - SizeY * 0.5f,
                           0.0f);

    // �E��
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + SizeX * 0.5f,
               y - SizeY * 0.5f,
                           0.0f);

    // ����O
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x - SizeX * 0.5f,
               y + SizeY * 0.5f,
                           0.0f);

    // �E��O
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x + SizeX * 0.5f,
               y + SizeY * 0.5f,
                           0.0f);

    // �`��I��
    glEnd();

    // 2D�`��ݒ胊�Z�b�g
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // �J�����ݒ����
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
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