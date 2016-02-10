/**************************************************************************************************

 @File   : [ Keyboard.cpp ] キーボードからの入力を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//-----Object-----//
#include "006_Tool/0060_Input/Keyboard.h"

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

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
Keyboard *Keyboard::Create()
{
    Keyboard* pKeyboard;
    pKeyboard = new Keyboard();
    pKeyboard->Init();

    return pKeyboard;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
void Keyboard::Init()
{
    HRESULT Result;
    LPDIRECTINPUT8 pInput = InputManager::GetInputDevice();

    // 配列の初期化
    for (int KeyID = 0; KeyID < MAX_KEY_NUM; KeyID++)
    {
        keyStatePress[KeyID]       = 0x00;
        keyStateTrigger[KeyID]     = 0x00;
        keyStateRelease[KeyID]     = 0x00;
        keyStateRepeat[KeyID]      = 0x00;
        keyStateRepeatCount[KeyID] = 1;
    }

    // キーボードデバイスオブジェクトの作成
    Result = pInput->CreateDevice(GUID_SysKeyboard, &pDeviceKeyboard, NULL);
    if (FAILED(Result))
    {
        MessageBox(NULL, "[ pDeviceKeyboard ] の作成に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return;
    }

    // キーボードデバイスのデータ形式を設定
    Result = pDeviceKeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(Result))
    {
        MessageBox(NULL, "[ pDeviceKeyboard ] のデータ形式の設定に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return;
    }

    // デバイスのインスタンスに対する協調レベルの設定
    Result = pDeviceKeyboard->SetCooperativeLevel(Main::windowHandle, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
    if (FAILED(Result))
    {
        MessageBox(NULL, "[ pDeviceKeyboard ] の協調モードの設定に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return;
    }

    // キーボードへのアクセス権を獲得
    pDeviceKeyboard->Acquire();
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Keyboard::Uninit()
{
    if (pDeviceKeyboard != NULL)
    {
        pDeviceKeyboard->Unacquire();
    }

    SafeRelease(pDeviceKeyboard);
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Keyboard::Update()
{
    BYTE keyState[MAX_KEY_NUM];    // キー情報の仲介
    int  RepeatRate = InputManager::RepeatRate;

    // 現在のキーボード入力状態を取得して、各種入力情報を更新する
    if (SUCCEEDED(pDeviceKeyboard->GetDeviceState(sizeof(keyState), keyState)))
    {
        for (int KeyID = 0; KeyID < MAX_KEY_NUM; KeyID++)
        {
            // Trigger 入力情報
            keyStateTrigger[KeyID] = (keyStatePress[KeyID] ^ keyState[KeyID]) & (keyState[KeyID]);

            // Release 入力情報
            keyStateRelease[KeyID] = (keyStatePress[KeyID] ^ keyState[KeyID]) & (keyStatePress[KeyID]);

            // Repeat 入力情報
            if (keyState[KeyID] == 0x80)
            {
                if (keyStateRepeatCount[KeyID] == 1)    // 初回の入力を真にする
                {
                    keyStateRepeat[KeyID] = 0x80;
                    keyStateRepeatCount[KeyID]++;

                }
                else if (keyStateRepeatCount[KeyID] <= RepeatRate)    // 一定のフレーム間は無効にする
                {
                    keyStateRepeat[KeyID] = 0x00;
                    keyStateRepeatCount[KeyID]++;

                }
                else if (keyStateRepeatCount[KeyID] > RepeatRate)     // 以後全て真にする
                {
                    keyStateRepeat[KeyID] = keyState[KeyID];
                }

            }
            else    // Repeat 状態の解除
            {
                keyStateRepeatCount[KeyID] = 1;
                keyStateRepeat[KeyID] = keyState[KeyID];
            }

            // キーボード情報の更新 (Press 入力情報)
            keyStatePress[KeyID] = keyState[KeyID];
        }
    }
    else
    {
        // キーボードへのアクセス権を再獲得
        pDeviceKeyboard->Acquire();
    }
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//