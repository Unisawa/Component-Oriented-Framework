/**************************************************************************************************

 @File   : [ Main.cpp ] 【 UniverseEngine 】のシステムを全て管理するメインクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "000_Main/Main.h"
#include "001_Constant/Constant.h"
#include "002_Manager/Manager.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#define CLASS_NAME "CoreClass"

//***********************************************************************************************//
//                                                                                               //
//  @Static Variable                                                                             //
//                                                                                               //
//***********************************************************************************************//
HWND         Main::windowHandle = NULL;
HINSTANCE    Main::instance     = NULL;
bool         Main::isWindow     = false;

unsigned int Main::frameRate    = 0;

/*===============================================================================================* 
  @Summary: プログラム起動時に最初に呼ばれ、Windowを生成、管理、破棄する
  @Details: None
 *===============================================================================================*/
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
    RECT  Rect;       // 画面サイズ
    MSG   Message;    // メッセージ情報
    Main* pMain;      // ゲーム用FPS管理など

    // メモリリークの検出開始
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

    // 分解能の設定
    timeBeginPeriod(1);

    // ウインドウクラスの設定
    WNDCLASSEX wcex =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, Main::WindowProcedure, 0, 0, hinstance, NULL,
        LoadCursor(NULL, IDC_ARROW), (HBRUSH)(COLOR_WINDOW + 1), NULL, CLASS_NAME, NULL
    };

    // クライアント領域サイズの補正
    SetRect(&Rect, 0, 0, (int)Constant::SCREEN_WIDTH, (int)Constant::SCREEN_HEIGHT);
    AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

    // ウインドウクラスの登録
    RegisterClassEx(&wcex);

    // ウィンドウ生成位置を中央に調整する
    RECT rcRect;
    Main::windowHandle = GetDesktopWindow();
    GetWindowRect(Main::windowHandle, &rcRect);

    // ウィンドウの生成
#ifdef _DEBUG
    Main::windowHandle = CreateWindowEx(0, CLASS_NAME, Constant::WINDOW_NAME.c_str(), WS_OVERLAPPEDWINDOW,
                                        (rcRect.right - (int)Constant::SCREEN_WIDTH) / 2 , (Rect.bottom - (int)Constant::SCREEN_HEIGHT) / 2,
                                        (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hinstance, NULL);
#else if _RELEASE
    Main::windowHandle = CreateWindowEx(0, CLASS_NAME, Constant::WINDOW_NAME.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                                        (rcRect.right - (int)Constant::SCREEN_WIDTH) / 2 , (Rect.bottom - (int)Constant::SCREEN_HEIGHT) / 2,
                                        (Rect.right - Rect.left), (Rect.bottom - Rect.top), NULL, NULL, hinstance, NULL);
#endif

    // ウィンドウの表示
    ShowWindow(Main::windowHandle, nCmdShow);
    UpdateWindow(Main::windowHandle);

    // 初期化処理
    Main::instance = hinstance;
    pMain = new Main();
    if (pMain->Init() == E_FAIL)    // 初期化失敗 プログラム終了
    {
        //-----終了処理-----//
        SafeDeleteUninit(pMain);

        // 分解能設定の解除
        timeEndPeriod(1);

        return NULL;
    }

    // Message Loop
    Message = pMain->MessageLoop();

    // ウィンドウクラスの登録解除
    UnregisterClass(CLASS_NAME, wcex.hInstance);

    //-----終了処理-----//
    SafeDeleteUninit(pMain);

    // 分解能設定の解除
    timeEndPeriod(1);

    return (int)Message.wParam;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
HRESULT Main::Init()
{
    Main::frameRate = 60;

    Debug::Log("Start Manager Init");

    pManager = new Manager();
    if (pManager->Init() == E_FAIL) return E_FAIL;

    return S_OK;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void Main::Uninit()
{
    Debug::Log("Start Manager Uninit");

    SafeDeleteUninit(pManager);
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void Main::Update()
{
    pManager->Update();

    // FPS表示用カウンタの更新
    //DebugManager::AddFrameCount();
}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void Main::Draw()
{
    pManager->Draw();
}

/*===============================================================================================* 
  @Summary: FPSを調整して更新、描画、プログラム終了の判定を管理する
  @Details: None
 *===============================================================================================*/
MSG Main::MessageLoop()
{
    MSG   Message;           // メッセージ情報
    DWORD dwExecLastTime;    // 最終実行時刻
    DWORD dwCurrentTime;     // 現在時刻

    // FPSの初期設定
    dwExecLastTime = timeGetTime();
    dwCurrentTime = 0;

    while (true)
    {
        if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE) != 0)
        {
            if (Message.message == WM_QUIT)
            {
                break;    // プログラム終了
            }
            else
            {
                // メッセージの解析と送出
                TranslateMessage(&Message);
                DispatchMessage(&Message);
            }
        }
        else
        {
            // 現在時刻取得
            dwCurrentTime = timeGetTime();

            // FPS 計算
            //DebugManager::CheckFPS(dwCurrentTime);

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / Main::frameRate))
            {
                dwExecLastTime = dwCurrentTime;

                //-----更新処理-----//
                Update();

                //-----描画処理-----//
                Draw();
            }
        }
    }

    return Message;
}

/*===============================================================================================* 
  @Summary: Window操作のコールバック関数
  @Details: None
 *===============================================================================================*/
LRESULT CALLBACK Main::WindowProcedure(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch(uMessage)
    {
        // ウィンドウ生成時の処理
        case WM_CREATE:
            break;

        // メッセージループの終了
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        // ウィンドウ終了ボタン押下時の確認
        case WM_CLOSE:

            // フルスクリーン中なら確認せずに終了する
            if( IDYES == MessageBox(hWnd, "終了しますか？" , "終了", MB_YESNO | MB_ICONQUESTION) )
            {
                DestroyWindow(hWnd);
                break;
            }

            return 0;
            break;
        
        // マウス操作時
        case WM_MOUSEMOVE:
            break;

        // 各種キー入力時
        case WM_KEYDOWN:
            switch(wParam)
            {
                // 終了処理
                case VK_ESCAPE:

                if( IDYES == MessageBox(hWnd, "終了しますか？" , "終了", MB_YESNO | MB_ICONQUESTION) )
                {
                    DestroyWindow(hWnd);
                }
                break;
            }
            break;

        // メニューバーからの設定処理
        case WM_COMMAND:
            break;

        default:
            break;
    }

    return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//