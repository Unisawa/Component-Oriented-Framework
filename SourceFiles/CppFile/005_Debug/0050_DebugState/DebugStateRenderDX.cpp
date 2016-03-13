/**************************************************************************************************

 @File   : [ DebugStateRenderDX.cpp ] 現在表示している描画物の一覧を表示するステートクラス
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
#include "005_Debug/DebugManagerDX.h"
#include "005_Debug/0050_DebugState/DebugStateRenderDX.h"

#include "004_Component/0040_RenderDX/RenderDX.h"
#include "004_Component/0040_RenderDX/RenderDXManager.h"
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
void DebugStateRenderDX::Init(DebugManagerDX* pDebugManagerDX)
{
    textColor  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pDebugFont = RenderDXManager::CreateFontText(20, 0, FW_BOLD, FALSE, "Terminal");

    indentSpace = "";

    selectRenderObject       = NULL;
    selectRenderNumber = 0;
    maxRenderNumber    = 0;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void DebugStateRenderDX::Uninit(DebugManagerDX* pDebugManagerDX)
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void DebugStateRenderDX::Update(DebugManagerDX* pDebugManagerDX)
{
    Keyboard* pKey = InputManager::GetKeyboard();

    // 初期化
    messegeHierarchy.clear();
    messegeInspector.clear();

    messegeHierarchy += "【 Render Hierarchy 】\n";
    messegeInspector += "【 Render Inspector 】\n";

    // SelectGamaObjectの移動
    //if (pKey->GetKeyboardPress(DIK_LSHIFT))
    {
        MoveRender();
    }
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void DebugStateRenderDX::Draw(DebugManagerDX* pDebugManagerDX)
{
    CheckRender();

    pDebugFont->DrawText(NULL, messegeHierarchy.c_str(), -1, &pDebugManagerDX->GetRectLeftUp(),   DT_LEFT, textColor);
    pDebugFont->DrawText(NULL, messegeInspector.c_str(), -1, &pDebugManagerDX->GetRectLeftDown(), DT_LEFT, textColor);
}

/*===============================================================================================* 
  @Summary: 現在生成しているRenderの名前を全て表示する
  @Details: None
 *===============================================================================================*/
void DebugStateRenderDX::CheckRender()
{
    // FPSの表示
    selectRenderCount = 0;
    char Temp[BUFFER_SIZE];

    std::list<RenderDX*>* pList = RenderDXManager::GetRenderDXList();
    std::list<Transform*> pChildren;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = pList[Layer].begin(); Iterator != pList[Layer].end(); ++Iterator)
        {
            // 選択中のRender の Transform の値を表示する
            if (selectRenderNumber == selectRenderCount)
            {
                selectRenderObject = (*Iterator)->gameObject;
                messegeInspector += "【 Transform 】\n";

                sprintf_s(Temp, "Position: (%f, %f, %f) \n", selectRenderObject->transform->GetPosition().x, selectRenderObject->transform->GetPosition().y, selectRenderObject->transform->GetPosition().z);
                messegeInspector += Temp;

                sprintf_s(Temp, "Rotision: (%f, %f, %f) \n", selectRenderObject->transform->GetRotation().x, selectRenderObject->transform->GetRotation().y, selectRenderObject->transform->GetRotation().z);
                messegeInspector += Temp;

                sprintf_s(Temp, "Scale   : (%f, %f, %f) \n", selectRenderObject->transform->GetScale().x, selectRenderObject->transform->GetScale().y, selectRenderObject->transform->GetScale().z);
                messegeInspector += Temp;

                messegeHierarchy += "→";
            }
            else
            {
                messegeHierarchy += "  ";
            }

            pChildren = (*Iterator)->transform->GetChildren();
            selectRenderCount++;

            if (pChildren.size() == 0)
            {
                messegeHierarchy += "  ";
                messegeHierarchy += (*Iterator)->gameObject->GetName();
                messegeHierarchy += "\n";
            }
            else
            {
                messegeHierarchy += "▼";
                messegeHierarchy += (*Iterator)->gameObject->GetName();
                messegeHierarchy += "\n";

                for (auto IteratorChild = pChildren.begin(); IteratorChild != pChildren.end(); ++IteratorChild)
                {
                    indentSpace += "  ";
                    CheckRenderChild((*IteratorChild)->gameObject);
                }
            }
        }
    }

    maxRenderNumber = selectRenderCount;
    if (selectRenderNumber >= maxRenderNumber)
    {
        selectRenderNumber = 0;
    }

    // 現シーンにオブジェクトが一つも存在しない場合
    if (maxRenderNumber == 0)
    {
        selectRenderObject = NULL;
    }
}

/*===============================================================================================* 
  @Summary: 対象のオブジェクトの子が存在するか確認して、あれば名前を表示する
  @Details: None
 *===============================================================================================*/
void DebugStateRenderDX::CheckRenderChild(GameObject* value)
{
    char Temp[BUFFER_SIZE];
    std::list<Transform*> pChildren;

    // 選択中のRender の Transform の値を表示する
    if (selectRenderNumber == selectRenderCount)
    {
        selectRenderObject = value;
        messegeInspector += "【 Transform 】\n";

        sprintf_s(Temp, "Position: (%f, %f, %f) \n", selectRenderObject->transform->GetPosition().x, selectRenderObject->transform->GetPosition().y, selectRenderObject->transform->GetPosition().z);
        messegeInspector += Temp;

        sprintf_s(Temp, "Rotision: (%f, %f, %f) \n", selectRenderObject->transform->GetRotation().x, selectRenderObject->transform->GetRotation().y, selectRenderObject->transform->GetRotation().z);
        messegeInspector += Temp;

        sprintf_s(Temp, "Scale   : (%f, %f, %f) \n", selectRenderObject->transform->GetScale().x, selectRenderObject->transform->GetScale().y, selectRenderObject->transform->GetScale().z);
        messegeInspector += Temp;

        messegeHierarchy += indentSpace + "→";
    }
    else
    {
        messegeHierarchy += indentSpace + "  ";
    }

    pChildren = value->transform->GetChildren();
    selectRenderCount++;

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
            CheckRenderChild((*IteratorChild)->gameObject);
        }
    }

    indentSpace.pop_back();
    indentSpace.pop_back();
}

/*===============================================================================================* 
  @Summary: 選択中のRenderのTransformを操作する
  @Details: None
 *===============================================================================================*/
void DebugStateRenderDX::MoveRender()
{
    Keyboard* pKey = InputManager::GetKeyboard();

    if (selectRenderObject == NULL) return;

    // オブジェクトの選択
    if (pKey->GetKeyboardTrigger(DIK_UP))
    {
        selectRenderNumber--;
        if (selectRenderNumber < 0)
        {
            selectRenderNumber = maxRenderNumber - 1;
        }
    }

    if (pKey->GetKeyboardTrigger(DIK_DOWN))
    {
        selectRenderNumber++;
        if (selectRenderNumber >(maxRenderNumber - 1))
        {
            selectRenderNumber = 0;
        }
    }

    // 選択オブジェクトの移動
    if (pKey->GetKeyboardPress(DIK_A))
    {
        Vector3 Pos = selectRenderObject->transform->GetPosition();
        Pos.x -= 1.0f;
        selectRenderObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_D))
    {
        Vector3 Pos = selectRenderObject->transform->GetPosition();
        Pos.x += 1.0f;
        selectRenderObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_W))
    {
        Vector3 Pos = selectRenderObject->transform->GetPosition();
        Pos.z += 1.0f;
        selectRenderObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_S))
    {
        Vector3 Pos = selectRenderObject->transform->GetPosition();
        Pos.z -= 1.0f;
        selectRenderObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_E))
    {
        Vector3 Pos = selectRenderObject->transform->GetPosition();
        Pos.y += 1.0f;
        selectRenderObject->transform->SetPosition(Pos);
    }

    if (pKey->GetKeyboardPress(DIK_Q))
    {
        Vector3 Pos = selectRenderObject->transform->GetPosition();
        Pos.y -= 1.0f;
        selectRenderObject->transform->SetPosition(Pos);
    }

    // 回転
    if (pKey->GetKeyboardPress(DIK_R))
    {
        Vector3 Rot = selectRenderObject->transform->GetRotation();
        Rot.x += 0.01f;
        selectRenderObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_F))
    {
        Vector3 Rot = selectRenderObject->transform->GetRotation();
        Rot.x -= 0.01f;
        selectRenderObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_T))
    {
        Vector3 Rot = selectRenderObject->transform->GetRotation();
        Rot.y += 0.01f;
        selectRenderObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_G))
    {
        Vector3 Rot = selectRenderObject->transform->GetRotation();
        Rot.y -= 0.01f;
        selectRenderObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_Y))
    {
        Vector3 Rot = selectRenderObject->transform->GetRotation();
        Rot.z += 0.01f;
        selectRenderObject->transform->SetRotation(Rot);
    }

    if (pKey->GetKeyboardPress(DIK_H))
    {
        Vector3 Rot = selectRenderObject->transform->GetRotation();
        Rot.z -= 0.01f;
        selectRenderObject->transform->SetRotation(Rot);
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
