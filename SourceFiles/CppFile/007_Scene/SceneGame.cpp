/**************************************************************************************************

 @File   : [ SceneGame.cpp ] ゲームシーンのクラス
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

//-----Manager-----//
#include "006_Tool/0060_Input/InputManager.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"
#include "004_Component/0040_RenderDX/00403_Texture/TextureDXManager.h"
#include "007_Scene/SceneManager.h"
#include "007_Scene/SceneTitle.h"
#include "007_Scene/SceneGame.h"
#include "007_Scene/SceneResult.h"

//-----Object-----//
#include "004_Component/Component.h"
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0042_GameObject/GameObject.h"
#include "004_Component/0040_RenderDX/00410_Base/Render2DDX.h"
#include "004_Component/0040_RenderDX/00410_Base/Render3DDX.h"
#include "004_Component/0040_RenderDX/00403_Texture/TextureDXManager.h"
#include "004_Component/0040_RenderDX/00421_MeshPolygon/MeshSphereDX.h"
#include "004_Component/0040_RenderDX/00420_Mesh/MeshRenderDX.h"

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
static GameObject* pTemp = NULL;

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
SceneGame::SceneGame()
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
SceneGame::~SceneGame()
{

}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void SceneGame::Init()
{
#ifdef USE_DIRECTX
    // GameObjectの生成、コンポーネントの追加テスト
    //GameObject* pGameObject0 = new GameObject;
    //pGameObject0->SetName("GameObject A");
    //pGameObject0->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject0->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DDX* pRender2D0 = pGameObject0->AddComponent<Render2DDX>();

    //GameObject* pGameObject1 = new GameObject;
    //pGameObject1->SetName("GameObject B");
    //pGameObject1->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF + Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject1->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DDX* pRender2D1 = pGameObject1->AddComponent<Render2DDX>();
    //pRender2D1->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

    //GameObject* pGameObject2 = new GameObject;
    //pGameObject2->SetName("GameObject C");
    //pGameObject2->transform->SetPosition(Vector3(Constant::SCREEN_WIDTH_HALF - Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_HEIGHT_HALF, 0.0f));
    //pGameObject2->transform->SetScale(Vector3(Constant::SCREEN_WIDTH_HALF / 2, Constant::SCREEN_WIDTH_HALF, 0.0f));
    //Render2DDX* pRender2D2 = pGameObject2->AddComponent<Render2DDX>();
    //pRender2D2->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

    //pTemp = pGameObject2;

    // 3Dポリゴン描画テスト
    Texture* pTexture;

    Render3DDX* pRender3D3 = NULL;

    GameObject* pGameObject3 = new GameObject("GameObject D");

    pRender3D3 = pGameObject3->AddComponent<Render3DDX>();
    pRender3D3->SetSize(100.0f, 0.0f, 100.0f);
    pRender3D3->SetTexture("FractalField000.bmp");
    pRender3D3->SetVertex();
    pTexture = pRender3D3->GetTexture();

    GameObject* pGameObject4 = new GameObject("GameObject F");
    unsigned int TextureID = pRender3D3->GetTextureID();

    pRender3D3 = pGameObject4->AddComponent<Render3DDX>();
    pRender3D3->transform->SetPosition(0.0f, 20.0f, 200.0f);
    pRender3D3->SetSize(100.0f, 0.0f, 100.0f);
    pRender3D3->SetTexture(pTexture);
    pRender3D3->SetVertex();

    // Mesh
    MeshSphereDX* pMesh;
    GameObject* pGameObject5 = new GameObject("MeshSphereDX");
    pGameObject5->transform->SetScale(10.0f, 10.0f, 10.0f);

    pMesh = pGameObject5->AddComponent<MeshSphereDX>();
    pMesh->SetUpSphere(20, 20, 5.0f);
    pMesh->GetMeshRender()->SetLightingOff();
#endif
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void SceneGame::Uninit()
{
    GameObjectManager::ReleaseAllScene();
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void SceneGame::Update()
{
    // 入力テスト
    Keyboard* pKey = InputManager::GetKeyboard();

    if (pKey->GetKeyboardTrigger(DIK_SPACE))
    {
        SceneManager::LoadLevel(&Scene::RESULT);
    }
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
