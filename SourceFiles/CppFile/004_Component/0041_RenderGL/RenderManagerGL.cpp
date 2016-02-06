/**************************************************************************************************

 @File   : [ RenderManagerGL.cpp ] OpneGLの描画を管理するクラス
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
#include "004_Component/0041_RenderGL/RenderManagerGL.h"

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
HDC   RenderManagerGL::hDC   = NULL;
HGLRC RenderManagerGL::hGLRC = NULL;

/*===============================================================================================* 
  @Summary: 生成処理
  @Details: None
 *===============================================================================================*/
RenderManagerGL *RenderManagerGL::Create()
{
    RenderManagerGL* pRenderManagerGL;
    pRenderManagerGL = new RenderManagerGL();
    if (FAILED(pRenderManagerGL->Init()))
    {
        MessageBox(NULL, "OpenGLによる描画設定に失敗しました。", "エラー発生", MB_ICONERROR | MB_OK);

        return NULL;
    }

    return pRenderManagerGL;
}

/*===============================================================================================* 
  @Summary: 初期化処理
  @Details: None
 *===============================================================================================*/
HRESULT RenderManagerGL::Init()
{
    // デバイスコンテキストの取得 OpenGL 初期化処理
    hDC = GetDC(Main::windowHandle);

    // OpenGL ピクセルフォーマットの作成
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Draw Flags
        PFD_TYPE_RGBA,                                                 // The kind of framebuffer. RGBA or palette.形式
        24,                                                            // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,                                              // ↑
        0,                                                             // ----
        0, 0, 0, 0, 0, 0,                                              // ↑ アキュムレーション バッファ
        32,                                                            // Number of bits for the depthbuffer
        1,                                                             // Number of bits for the stencilbuffer
        0,                                                             // Number of Aux buffers in the framebuffer. 未サポート
        PFD_MAIN_PLANE,
        0, 0, 0, 0
    };

    // ピクセルフォーマットの選択
    int PixelFormat = ChoosePixelFormat(hDC, &pfd);

    // OpenGLデバイスコンテキストに指定のピクセルフォーマットをセット
    SetPixelFormat(hDC, PixelFormat, &pfd);

    // OpenGL コンテキストを作成
    hGLRC = wglCreateContext(hDC);

    // 作成したコンテキストをカレントに設定
    wglMakeCurrent(hDC, hGLRC);

    // テクスチャの有効化
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    return S_OK;
}

/*===============================================================================================* 
  @Summary: 終了処理
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::Uninit()
{
    // OpenGL 終了処理
    wglMakeCurrent(NULL, NULL);            // カレントコンテキストを無効にする
    wglDeleteContext(hGLRC);               // カレントコンテキストを削除
    ReleaseDC(Main::windowHandle, hDC);    // デバイスコンテキスト解放

    hGLRC = NULL;
    hDC   = NULL;
}

/*===============================================================================================* 
  @Summary: 更新処理
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::Update()
{

}

/*===============================================================================================* 
  @Summary: 描画処理
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::Draw()
{
    // 画面のクリア
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // フロントバッファとバックバッファの入れ替え
    SwapBuffers(hDC);
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//