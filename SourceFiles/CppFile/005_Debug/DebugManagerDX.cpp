/**************************************************************************************************

 @File   : [ DebugManagerDX.cpp ] DirectXのデバッグモードを制御するクラス
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
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateNoneDX.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateDebugDX.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"

#include "005_Debug/DebugManagerDX.h"
#include "006_Tool/0060_Input/InputManager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define BUFFER_SIZE (256)    // DebugManagerDX::Printを使用した際の最大文字数

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
DWORD DebugManagerDX::currentTime = 0;
DWORD DebugManagerDX::lastTimeFPS = 0;
DWORD DebugManagerDX::frameCount  = 0;
int   DebugManagerDX::countFPS    = 0;

std::string DebugManagerDX::messegeFree;
std::string DebugManagerDX::messegeHierarchy;
std::string DebugManagerDX::messegeInspector;

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
DebugManagerDX::DebugManagerDX()
{

}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
DebugManagerDX::~DebugManagerDX()
{

}

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
DebugManagerDX *DebugManagerDX::Create()
{
    DebugManagerDX* pDebugManagerDX;
    pDebugManagerDX = new DebugManagerDX();
    pDebugManagerDX->Init();

    return pDebugManagerDX;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
#ifdef _DEBUG
void DebugManagerDX::Init()
{
    currentTime = 0;
    lastTimeFPS = 0;
    frameCount  = 0;
    countFPS    = 0;

    textColor  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pDebugFont = RenderDXManager::CreateFontText(20, 0, FW_BOLD, FALSE, "Terminal");

    indentSpace = "";

    selectGameObject       = NULL;
    selectGameObjectNumber = 0;
    maxGameObjectNumber    = 0;
    isDebugMode = false;

    freeRect.left   = (LONG) Constant::SCREEN_WIDTH / 3;
    freeRect.right  = (LONG) Constant::SCREEN_WIDTH;
    freeRect.top    = (LONG) Constant::SCREEN_HEIGHT * 2 / 3;
    freeRect.bottom = (LONG) Constant::SCREEN_HEIGHT;
    
    hierarchyRect.left   = 0;
    hierarchyRect.right  = (LONG) Constant::SCREEN_WIDTH / 3;
    hierarchyRect.top    = 0;
    hierarchyRect.bottom = (LONG) Constant::SCREEN_HEIGHT * 2 / 3;

    inspectorRect.left   = 0;
    inspectorRect.right  = (LONG) Constant::SCREEN_WIDTH / 3;
    inspectorRect.top    = (LONG) Constant::SCREEN_HEIGHT * 2 / 3;
    inspectorRect.bottom = (LONG) Constant::SCREEN_HEIGHT;
}
#else
void DebugManagerDX::Init()
{

}
#endif

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
#ifdef _DEBUG
void DebugManagerDX::Uninit()
{
    SafeRelease(pDebugFont);
}
#else
void DebugManagerDX::Uninit()
{

}
#endif

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
#ifdef _DEBUG
void DebugManagerDX::Update()
{
    messegeFree.clear();
    messegeHierarchy.clear();
    messegeInspector.clear();

    messegeFree      += " -Free Messege Space- \n";
    messegeInspector += "【 Inspector 】 \n";

    Keyboard* pKey = InputManager::GetKeyboard();

    // デバッグモードの起動
    if (pKey->GetKeyboardTrigger(DIK_F1))
    {
        isDebugMode = isDebugMode ? false : true;
        if (isDebugMode)
        {
            Manager::GetRenderDXManager()->ChangeState(&ScreenStateDX::debug);
        }
        else
        {
            Manager::GetRenderDXManager()->ChangeState(&ScreenStateDX::none);
        }
    }

    // SelectGamaObjectの移動
    if (pKey->GetKeyboardPress(DIK_LSHIFT))
    {
        MoveGameObject();
    }
}
#else
void DebugManagerDX::Update()
{

}
#endif

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
#ifdef _DEBUG
void DebugManagerDX::Draw()
{
    // デバッグモード時のみ描画
    if (!isDebugMode) return;

    CheckGameObject();

    pDebugFont->DrawText(NULL, messegeFree.c_str(), -1, &freeRect, DT_LEFT, textColor);
    pDebugFont->DrawText(NULL, messegeHierarchy.c_str(), -1, &hierarchyRect, DT_LEFT, textColor);
    pDebugFont->DrawText(NULL, messegeInspector.c_str(), -1, &inspectorRect, DT_LEFT, textColor);
}
#else
void DebugManagerDX::Draw()
{

}
#endif

/*===============================================================================================* 
  @Summary: 現在生成しているGameObjectの名前を全て表示する
  @Details: None
 *===============================================================================================*/
void DebugManagerDX::CheckGameObject()
{
    // FPSの表示
    selectGameObjectCount = 0;
    char Temp[BUFFER_SIZE];
    sprintf_s(Temp, "【 FPS : %d 】\n\n", countFPS);
    messegeHierarchy += Temp;
    //Debug::Log("CountFPS: %d", countFPS);

    messegeHierarchy += "【 Hierarchy 】\n";

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
  @Summary: 
  @Details: 
 *===============================================================================================*/
void DebugManagerDX::CheckGameObjectChild(GameObject* value)
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
void DebugManagerDX::MoveGameObject()
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
  @Summary: FPSを計測する
  @Details: None
 *===============================================================================================*/
#ifdef _DEBUG
void DebugManagerDX::CheckFPS(DWORD NowTime)
{
    // FPS計算
    currentTime = NowTime;

    if ((NowTime - lastTimeFPS) >= 500)    // 500 / 1000s = 0.5s
    {
        countFPS = (frameCount * 1000) / (NowTime - lastTimeFPS);
        lastTimeFPS = NowTime;
        frameCount = 0;
    }
}
#else
void DebugManagerDX::CheckFPS(DWORD NowTime)
{

}
#endif

/*===============================================================================================* 
  @Summary: FPS計測のためのカウント追加
  @Details: None
 *===============================================================================================*/
#ifdef _DEBUG
void DebugManagerDX::AddframeCount()
{
    frameCount++;
}
#else
void DebugManagerDX::AddframeCount()
{

}
#endif

/*===============================================================================================* 
  @Summary: スクリーンへ文字を表示させるための処理
  @Details: None
 *===============================================================================================*/
#ifdef _DEBUG
void DebugManagerDX::Print(std::string String, ...)
{
    va_list Argument;
    CHAR    Buffer[BUFFER_SIZE];

    // 可変引数から文字列へ
    va_start(Argument, String);
    vsprintf_s(Buffer, String.c_str(), Argument);
    va_end(Argument);

    messegeFree += Buffer;
    messegeFree += "\n";
}
#else
void DebugManagerDX::Print(std::string String, ...)
{

}
#endif

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
