/**************************************************************************************************

 @File   : [ Keyboard.h ] キーボードからの入力を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define MAX_KEY_NUM (256)

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class Keyboard
{
public:
     Keyboard() {}
    ~Keyboard() {}

    static Keyboard* Create();

    void Init();
    void Uninit();
    void Update();

    //-----Input State-----//
    bool GetKeyboardPress(int KeyID)   { return (keyStatePress[KeyID] & 0x80) ? true : false; }
    bool GetKeyboardTrigger(int KeyID) { return (keyStateTrigger[KeyID] & 0x80) ? true : false; }
    bool GetKeyboardRelease(int KeyID) { return (keyStateRelease[KeyID] & 0x80) ? true : false; }
    bool GetKeyboardRepeat(int KeyID)  { return (keyStateRepeat[KeyID] & 0x80) ? true : false; }

private:
    LPDIRECTINPUTDEVICE8 pDeviceKeyboard;

    BYTE keyStatePress[MAX_KEY_NUM];               // キーボード: Press   情報
    BYTE keyStateTrigger[MAX_KEY_NUM];             // キーボード: Trigger 情報
    BYTE keyStateRelease[MAX_KEY_NUM];             // キーボード: Release 情報
    BYTE keyStateRepeat[MAX_KEY_NUM];              // キーボード: Repeat  情報
    int  keyStateRepeatCount[MAX_KEY_NUM];         // キーボード: Repeat  判定に必要
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//