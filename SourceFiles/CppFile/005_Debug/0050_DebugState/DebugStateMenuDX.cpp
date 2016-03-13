/**************************************************************************************************

 @File   : [ DebugStateMenuDX.cpp ] 各種デバッグモードの一覧を表示するステートクラス
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

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderDXManager.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateNoneDX.h"
#include "004_Component/0040_RenderDX/00402_ScreenState/ScreenStateDebugDX.h"

#include "005_Debug/DebugManagerDX.h"
#include "005_Debug/0050_DebugState/DebugStateNoneDX.h"
#include "005_Debug/0050_DebugState/DebugStateMenuDX.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void DebugStateMenuDX::Init(DebugManagerDX* pDebugManagerDX)
{
    textColor  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pDebugFont = RenderDXManager::CreateFontText(20, 0, FW_BOLD, FALSE, "Terminal");

    // 初期化
    messegeMenu.clear();
    messegeMenu += "【 Debug Menu 】\n\n";

    messegeMenu += " 【 F1 : Debug Menu 】\n";
    messegeMenu += "  (デバッグモード時の機能の一覧を表示する)\n\n";

    messegeMenu += " 【 F2 : GameObject List 】\n";
    messegeMenu += "  (現在管理しているGameObjectの一覧を表示する)\n\n";

    messegeMenu += " 【 F3 : RenderObject List 】\n";
    messegeMenu += "  (現在表示しているRenderの一覧を表示する)\n\n";

    messegeMenu += "\n 【 F1 : Debug Mode End 】\n";
    messegeMenu += "  (デバッグモードを終了する)\n\n";

    pDebugManagerDX->SetDebugMode(false);
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void DebugStateMenuDX::Uninit(DebugManagerDX* pDebugManagerDX)
{

}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void DebugStateMenuDX::Update(DebugManagerDX* pDebugManagerDX)
{
    Keyboard* pKey = InputManager::GetKeyboard();

    // デバッグモードの起動
    if (pKey->GetKeyboardTrigger(DIK_F1))
    {
        bool isDebugMode = pDebugManagerDX->IsDebugMode();
        isDebugMode = isDebugMode ? false : true;
        if (isDebugMode)
        {
            Manager::GetRenderDXManager()->ChangeState(&ScreenStateDX::debug);
        }
        else
        {
            Manager::GetRenderDXManager()->ChangeState(&ScreenStateDX::none);
            pDebugManagerDX->ChangeState(&DebugStateDX::none);
        }

        pDebugManagerDX->SetDebugMode(isDebugMode);
        if (!isDebugMode) return;
    }
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void DebugStateMenuDX::Draw(DebugManagerDX* pDebugManagerDX)
{
    if (!pDebugManagerDX->IsDebugMode()) return;

    pDebugFont->DrawText(NULL, messegeMenu.c_str(), -1, &pDebugManagerDX->GetRectLeftUp(), DT_LEFT, textColor);
    pDebugFont->DrawText(NULL, pDebugManagerDX->GetFreeMessege().c_str(), -1, &pDebugManagerDX->GetRectBottom(), DT_LEFT, textColor);
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
