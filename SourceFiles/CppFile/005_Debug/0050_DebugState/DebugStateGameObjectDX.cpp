/**************************************************************************************************

 @File   : [ DebugStateGameObjectDX.cpp ] 現在表示しているGameObjectの一覧を表示するステートクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "001_Manager/Manager.h"
#include "002_Constant/Constant.h"

//-----Object-----//
#include "005_Debug/0050_DebugState/DebugStateGameObjectDX.h"

#include "004_Component/0042_GameObject/GameObjectManager.h"
#include "004_Component/0042_GameObject/Transform.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

#define BUFFER_SIZE (256)    // DebugManagerDX::Printを使用した際の最大文字数

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void DebugStateGameObjectDX::Init(DebugManagerDX* pDebugManagerDX)
{
    textColor  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pDebugFont = RenderDXManager::CreateFontText(20, 0, FW_BOLD, FALSE, "Terminal");

    indentSpace = "";

    selectGameObject       = NULL;
    selectGameObjectNumber = 0;
    maxGameObjectNumber    = 0;

    hierarchyRect.left   = 0;
    hierarchyRect.right  = (LONG) Constant::SCREEN_WIDTH / 3;
    hierarchyRect.top    = 0;
    hierarchyRect.bottom = (LONG) Constant::SCREEN_HEIGHT * 2 / 3;

    inspectorRect.left   = 0;
    inspectorRect.right  = (LONG) Constant::SCREEN_WIDTH / 3;
    inspectorRect.top    = (LONG) Constant::SCREEN_HEIGHT * 2 / 3;
    inspectorRect.bottom = (LONG) Constant::SCREEN_HEIGHT;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void DebugStateGameObjectDX::Uninit(DebugManagerDX* pDebugManagerDX)
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void DebugStateGameObjectDX::Update(DebugManagerDX* pDebugManagerDX)
{
    Keyboard* pKey = InputManager::GetKeyboard();

    // 初期化
    messegeHierarchy.clear();
    messegeInspector.clear();

    messegeHierarchy += "【 GameObject Hierarchy 】\n";
    messegeInspector += "【 GameObject Inspector 】\n";

    // SelectGamaObjectの移動
    //if (pKey->GetKeyboardPress(DIK_LSHIFT))
    {
        MoveGameObject();
    }
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void DebugStateGameObjectDX::Draw(DebugManagerDX* pDebugManagerDX)
{
    CheckGameObject();

    pDebugFont->DrawText(NULL, messegeHierarchy.c_str(), -1, &hierarchyRect, DT_LEFT, textColor);
    pDebugFont->DrawText(NULL, messegeInspector.c_str(), -1, &inspectorRect, DT_LEFT, textColor);
}

/*===============================================================================================* 
  @Summary: 現在生成しているGameObjectの名前を全て表示する
  @Details: None
 *===============================================================================================*/
void DebugStateGameObjectDX::CheckGameObject()
{
    // FPSの表示
    selectGameObjectCount = 0;
    char Temp[BUFFER_SIZE];

    std::list<GameObject*>* pList = GameObjectManager::GetGameObjectList();
    std::list<Transform*> pChildren;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = pList[Layer].begin(); Iterator != pList[Layer].end(); ++Iterator)
        {
            // 選択中のGameObject の Transform の値を表示する
            if (selectGameObjectNumber == selectGameObjectCount)
            {
                selectGameObject = (*Iterator);
                messegeInspector += "【 Transform 】\n";

                sprintf_s(Temp, "Position: (%f, %f, %f) \n", selectGameObject->transform->GetPosition().x, selectGameObject->transform->GetPosition().y, selectGameObject->transform->GetPosition().z);
                messegeInspector += Temp;

                sprintf_s(Temp, "Rotision: (%f, %f, %f) \n", selectGameObject->transform->GetRotation().x, selectGameObject->transform->GetRotation().y, selectGameObject->transform->GetRotation().z);
                messegeInspector += Temp;

                sprintf_s(Temp, "Scale   : (%f, %f, %f) \n", selectGameObject->transform->GetScale().x, selectGameObject->transform->GetScale().y, selectGameObject->transform->GetScale().z);
                messegeInspector += Temp;

                messegeHierarchy += "→";
            }
            else
            {
                messegeHierarchy += "  ";
            }

            pChildren = (*Iterator)->transform->GetChildren();
            selectGameObjectCount++;

            if (pChildren.size() == 0)
            {
                messegeHierarchy += "  ";
                messegeHierarchy += (*Iterator)->GetName();
                messegeHierarchy += "\n";
            }
            else
            {
                messegeHierarchy += "▼";
                messegeHierarchy += (*Iterator)->GetName();
                messegeHierarchy += "\n";

                for (auto IteratorChild = pChildren.begin(); IteratorChild != pChildren.end(); ++IteratorChild)
                {
                    indentSpace += "  ";
                    CheckGameObjectChild((*IteratorChild)->gameObject);
                }
            }
        }
    }

    maxGameObjectNumber = selectGameObjectCount;
    if (selectGameObjectNumber >= maxGameObjectNumber)
    {
        selectGameObjectNumber = 0;
    }

    // 現シーンにオブジェクトが一つも存在しない場合
    if (maxGameObjectNumber == 0)
    {
        selectGameObject = NULL;
    }
}

/*===============================================================================================* 
  @Summary: 対象のオブジェクトの子が存在するか確認して、あれば名前を表示する
  @Details: None
 *===============================================================================================*/
void DebugStateGameObjectDX::CheckGameObjectChild(GameObject* value)
{
    char Temp[BUFFER_SIZE];
    std::list<Transform*> pChildren;

    // 選択中のGameObject の Transform の値を表示する
    if (selectGameObjectNumber == selectGameObjectCount)
    {
        selectGameObject = value;
        messegeInspector += "【 Transform 】\n";

        sprintf_s(Temp, "Position: (%f, %f, %f) \n", selectGameObject->transform->GetPosition().x, selectGameObject->transform->GetPosition().y, selectGameObject->transform->GetPosition().z);
        messegeInspector += Temp;

        sprintf_s(Temp, "Rotision: (%f, %f, %f) \n", selectGameObject->transform->GetRotation().x, selectGameObject->transform->GetRotation().y, selectGameObject->transform->GetRotation().z);
        messegeInspector += Temp;

        sprintf_s(Temp, "Scale   : (%f, %f, %f) \n", selectGameObject->transform->GetScale().x, selectGameObject->transform->GetScale().y, selectGameObject->transform->GetScale().z);
        messegeInspector += Temp;

        messegeHierarchy += indentSpace + "→";
    }
    else
    {
        messegeHierarchy += indentSpace + "  ";
    }

    pChildren = value->transform->GetChildren();
    selectGameObjectCount++;

    if (pChildren.size() == 0)
    {
        messegeHierarchy += indentSpace;
        messegeHierarchy += value->GetName();
        messegeHierarchy += "\n";
    }
    else
    {
        messegeHierarchy += indentSpace + "▼";
        messegeHierarchy += value->GetName();
        messegeHierarchy += "\n";

        for (auto IteratorChild = pChildren.begin(); IteratorChild != pChildren.end(); ++IteratorChild)
        {
            indentSpace += "  ";
            CheckGameObjectChild((*IteratorChild)->gameObject);
        }
    }

    indentSpace.pop_back();
    indentSpace.pop_back();
}

/*===============================================================================================* 
  @Summary: 選択中のGameObjectのTransformを操作する
  @Details: None
 *===============================================================================================*/
void DebugStateGameObjectDX::MoveGameObject()
{
    Keyboard* pKey = InputManager::GetKeyboard();

    if (selectGameObject == NULL) return;

    // オブジェクトの選択
    if (pKey->GetKeyboardTrigger(DIK_UP))
    {
        selectGameObjectNumber--;
        if (selectGameObjectNumber < 0)
        {
            selectGameObjectNumber = maxGameObjectNumber - 1;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_DOWN))
    {
        selectGameObjectNumber++;
        if (selectGameObjectNumber >(maxGameObjectNumber - 1))
        {
            selectGameObjectNumber = 0;
        }
    }

    // 選択オブジェクトの移動
    if (pKey->GetKeyboardPress(DIK_A))
    {
        Vector3 Pos = selectGameObject->transform->GetPosition();
        Pos.x -= 1.0f;
        selectGameObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_D))
    {
        Vector3 Pos = selectGameObject->transform->GetPosition();
        Pos.x += 1.0f;
        selectGameObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_W))
    {
        Vector3 Pos = selectGameObject->transform->GetPosition();
        Pos.z += 1.0f;
        selectGameObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_S))
    {
        Vector3 Pos = selectGameObject->transform->GetPosition();
        Pos.z -= 1.0f;
        selectGameObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_E))
    {
        Vector3 Pos = selectGameObject->transform->GetPosition();
        Pos.y += 1.0f;
        selectGameObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_Q))
    {
        Vector3 Pos = selectGameObject->transform->GetPosition();
        Pos.y -= 1.0f;
        selectGameObject->transform->SetPosition(Pos);
    }

    // 回転
    if (pKey->GetKeyboardPress(DIK_R))
    {
        Vector3 Rot = selectGameObject->transform->GetRotation();
        Rot.x += 0.01f;
        selectGameObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_F))
    {
        Vector3 Rot = selectGameObject->transform->GetRotation();
        Rot.x -= 0.01f;
        selectGameObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_T))
    {
        Vector3 Rot = selectGameObject->transform->GetRotation();
        Rot.y += 0.01f;
        selectGameObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_G))
    {
        Vector3 Rot = selectGameObject->transform->GetRotation();
        Rot.y -= 0.01f;
        selectGameObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_Y))
    {
        Vector3 Rot = selectGameObject->transform->GetRotation();
        Rot.z += 0.01f;
        selectGameObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_H))
    {
        Vector3 Rot = selectGameObject->transform->GetRotation();
        Rot.z -= 0.01f;
        selectGameObject->transform->SetRotation(Rot);
    }
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
