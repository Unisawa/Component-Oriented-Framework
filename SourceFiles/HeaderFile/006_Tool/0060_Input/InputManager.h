/**************************************************************************************************

 @File   : [ InputManager.h ] 全ての入力情報を管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Link Library                                                                                //
//                                                                                               //
//***********************************************************************************************//
#pragma comment (lib, "dinput8.lib")    // 入力システム関連

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "002_Manager/Manager.h"

//-----Input-----//
#define  DIRECTINPUT_VERSION (0x0800)    // DirectInput のバージョン指定-(0x0800)
#include "dinput.h"
//#include "Mouse.h"
#include "006_Tool/0060_Input/Keyboard.h"
//#include "Joystick.h"
//#include "InputVirtualKey.h"

//-----Object-----//
#include "004_Component/0040_RenderDX/RenderManagerDX.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class InputManager
{
public:
     InputManager() {}
    ~InputManager() {}

    static InputManager* Create();

    void Init();
    void Uninit();
    void Update();

    static LPDIRECTINPUT8 GetInputDevice(void) { return pDInput; }

    //static Mouse*           GetMouse()      { return pMouse; }
    static Keyboard*        GetKeyboard()   { return pKeyboard; }
    //static Joystick*        GetJoystick()   { return pJoystick; }
    //static InputVirtualKey* GetVirtualKey() { return pVirtualKey; }

    static int RepeatRate;    // キー入力 リピート判定までのフレーム数

private:
    static LPDIRECTINPUT8 pDInput;

    //static Mouse*    pMouse;
    static Keyboard* pKeyboard;
    //static Joystick* pJoystick;

    //static InputVirtualKey* pVirtualKey;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//