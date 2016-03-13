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
#include "000_Main/Main.h"
#include "001_Manager/Manager.h"
#include "002_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderDXManager.h"

#include "005_Debug/DebugManagerDX.h"
#include "005_Debug/0050_DebugState/DebugStateDX.h"
#include "005_Debug/0050_DebugState/DebugStateNoneDX.h"
#include "005_Debug/0050_DebugState/DebugStateMenuDX.h"
#include "005_Debug/0050_DebugState/DebugStateGameObjectDX.h"
#include "005_Debug/0050_DebugState/DebugStateRenderDX.h"

#include "007_Scene/SceneManager.h"

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
DWORD DebugManagerDX::currentTime = 0;
DWORD DebugManagerDX::lastTimeFPS = 0;
DWORD DebugManagerDX::frameCount  = 0;
int   DebugManagerDX::countFPS    = 0;

std::string DebugManagerDX::messegeFree;

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

    pDebugFont = RenderDXManager::CreateFontText(20, 0, FW_BOLD, FALSE, "Terminal");

    isDebugMode = false;
    isWireFrame = false;

    pDebugStateDX = &DebugStateDX::none;
    pDebugStateDX->Init(this);

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
    // 初期メッセージの設定
    SetFreeMessege();

    // デバッグ状態の切り替え
    SelectDebugState();

    // デバッグ時共通の処理
    ChangeDebugMode();

    // デバッグの各種状態の更新
    pDebugStateDX->Update(this);
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

    pDebugStateDX->Draw(this);
}
#else
void DebugManagerDX::Draw()
{

}
#endif

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
  @Summary: デバッグ状態を変更する
  @Details: None
 *===============================================================================================*/
void DebugManagerDX::ChangeState(DebugStateDX* pState)
{
    if (pDebugStateDX == pState)
    {
        return;
    }

    pDebugStateDX = pState;
    pDebugStateDX->Init(this);
}

/*===============================================================================================* 
  @Summary: フリーメッセージの編集
  @Details: None
 *===============================================================================================*/
void DebugManagerDX::SetFreeMessege()
{
    char Temp[BUFFER_SIZE];

    messegeFree.clear();
    messegeFree += " -Free Messege Space- \n";

    // FPS表示
    sprintf_s(Temp, "【 FPS: %d 】\n", countFPS);
    messegeFree += Temp;

    DebugManagerDX::Print("【 現在のシーン: " + Manager::GetSceneManager()->GetNowSceneName() + " 】");

}

/*===============================================================================================* 
  @Summary: デバッグステートを選択・切り替える処理
  @Details: None
 *===============================================================================================*/
void DebugManagerDX::SelectDebugState()
{
    Keyboard* pKey = InputManager::GetKeyboard();

    // デバッグモードの変更
    if (pKey->GetKeyboardTrigger(DIK_F1))
    {
        ChangeState(&DebugStateDX::menu);
    }
    else if (pKey->GetKeyboardTrigger(DIK_F2))
    {
        ChangeState(&DebugStateDX::gameObject);
    }
    else if (pKey->GetKeyboardTrigger(DIK_F3))
    {
        ChangeState(&DebugStateDX::render);
    }
}

/*===============================================================================================* 
  @Summary: デバッグ状態全体に変更を与える処理
  @Details: None
 *===============================================================================================*/
void DebugManagerDX::ChangeDebugMode()
{
    Keyboard* pKey = InputManager::GetKeyboard();

    // ワイヤーフレームの表示
    if (pKey->GetKeyboardTrigger(DIK_1))
    {
        isWireFrame = isWireFrame ? false : true;

        if (isWireFrame)
        {
            RenderDXManager::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
        }
        else
        {
            RenderDXManager::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
        }
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
