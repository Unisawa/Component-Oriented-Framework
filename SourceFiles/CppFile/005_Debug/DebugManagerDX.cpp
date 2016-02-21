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

    isDebugMode = false;

    freeRect.left   = 0;
    freeRect.right  = (LONG) Constant::SCREEN_WIDTH;
    freeRect.top    = (LONG) Constant::SCREEN_HEIGHT * 2 / 3;
    freeRect.bottom = (LONG) Constant::SCREEN_HEIGHT;
    
    hierarchyRect.left   = 0;
    hierarchyRect.right  = (LONG) Constant::SCREEN_WIDTH / 3;
    hierarchyRect.top    = 0;
    hierarchyRect.bottom = (LONG) Constant::SCREEN_HEIGHT * 2 / 3;
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

    messegeFree += " -FreeMessege Space- \n";

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
    char Temp[BUFFER_SIZE];

    sprintf_s(Temp, "【 FPS : %d 】\n\n", countFPS);
    messegeHierarchy += Temp;

    messegeHierarchy += "【 Hierarchy 】\n";

    std::list<GameObject*>* pList = GameObjectManager::GetGameObjectList();

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = pList[Layer].begin(); Iterator != pList[Layer].end(); ++Iterator)
        {
            if ((*Iterator)->transform->GetParent() == NULL)
            {
                messegeHierarchy += "  ";
            }
            else
            {
                messegeHierarchy += "▼";
            }

            messegeHierarchy += (*Iterator)->GetName();
            messegeHierarchy += "\n";
        }
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
