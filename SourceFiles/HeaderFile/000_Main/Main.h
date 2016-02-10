/**************************************************************************************************

 @File   : [ Main.h ] 【 UniverseEngine 】のシステムを全て管理するメインクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

//***********************************************************************************************//
//                                                                                               //
//  @Link Library                                                                                //
//                                                                                               //
//***********************************************************************************************//
#pragma comment (lib, "winmm.lib")     // Windows システム関連

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Find Memory Leak-----//
#define  _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//-----Default Include-----//
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//-----STL-----//
#include <String>
#include <list>

//-----Manager-----//
#include "002_Manager/Manager.h"
#include "006_Tool/0060_Input/InputManager.h"

//-----Debug-----//
#include "005_Debug/Debug.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//

//-----Memory Leak Report-----//
#ifdef _DEBUG
    #ifndef DBG_NEW
        #define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
        #define new DBG_NEW
    #endif
#endif

//-----Safe Memory Delete-----//
template <typename T>
inline void SafeDelete(T*& pPointer)    // NULLでないならポインタ削除
{
    if (pPointer != NULL)
    {
        delete (pPointer);
        (pPointer) = NULL;
    }
}

template <typename T>
inline void SafeDeleteArray(T*& pPointer)    // NULLでないなら配列ポインタ削除
{
    if (pPointer != NULL)
    {
        delete[] (pPointer);
        (pPointer) = NULL;
    }
}

template <typename T>
inline void SafeUninit(T*& pPointer)    // NULLでないならそのポインタのUninit()を実行
{
    if (pPointer != NULL)
    {
        (pPointer)->Uninit();
        (pPointer) = NULL;
    }
}

template <typename T>
inline void SafeDeleteUninit(T*& pPointer)    // NULLでないならそのポインタのUninit()を実行後、削除
{
    if (pPointer != NULL)
    {
        (pPointer)->Uninit();
        delete (pPointer);
        (pPointer) = NULL;
    }
}

//-----Safe Memory Release-----//
template <typename T>
inline void SafeRelease(T*& pPointer)    // NULLでないならそのポインタのRelease()を実行
{
    if (pPointer != NULL)
    {
        (pPointer)->Release();
        (pPointer) = NULL;
    }
}

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class Manager;

class Main
{
public:
     Main() {};
    ~Main() {};

    HRESULT Init();
    void    Uninit();
    void    Update();
    void    Draw();
    MSG     MessageLoop();

    static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Win32APIのウィンドウ情報
    static HWND      windowHandle;
    static HINSTANCE instance;
    static bool      isWindow;

    static unsigned int frameRate;

private:
    Manager* pManager;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//