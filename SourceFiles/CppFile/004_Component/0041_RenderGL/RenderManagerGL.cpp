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
#include "001_Constant/Constant.h"

//-----Object-----//
#include "004_Component/0041_RenderGL/RenderGL.h"
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

std::list<RenderGL*> RenderManagerGL::renderGLList[GameObject::LAYER_MAX];

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

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        renderGLList[Layer].clear();
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
    // 既にGameObjectManager::ReleaseAll()でRenderコンポーネントは削除されているのでリンクを解除する
    UnLinkListAll();

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
    UpdateAll();
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

    // 描画
    DrawAll();

    // フロントバッファとバックバッファの入れ替え
    SwapBuffers(hDC);
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderを更新する
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::UpdateAll()
{
    for (int Cnt = 0; Cnt < GameObject::LAYER_MAX; ++Cnt)
    {
        for (auto Iterator = renderGLList[Cnt].begin(); Iterator != renderGLList[Cnt].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Update();
            }
        }
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderの描画をする
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::DrawAll()
{
    // 描画の高速化
    CalculateZSortAll();
    ZSort();

    for (int Cnt = 0; Cnt < GameObject::LAYER_MAX; ++Cnt)
    {
        // 2Dカメラ設定
        if (Cnt == GameObject::LAYER::OBJECT2D_OPACITY_ONE)
        {
            // 2D描画設定
            glDisable(GL_LIGHTING);
            glDisable(GL_DEPTH_TEST);

            // 正射影行列
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0f, Constant::SCREEN_WIDTH, Constant::SCREEN_HEIGHT, 0.0f, 0.0f, 10000.0f);
            glPushMatrix();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }

        for (auto Iterator = renderGLList[Cnt].begin(); Iterator != renderGLList[Cnt].end(); ++Iterator)
        {
            if ((*Iterator)->enabled)
            {
                (*Iterator)->Draw();
            }
        }
    }

    // 2Dカメラ設定解除
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    // 2D描画設定リセット
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderをリストから解除する
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::UnLinkListAll()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        renderGLList[Layer].clear();
    }
}

/*===============================================================================================*
  @Summary: 登録された全てのRenderを削除する
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::ReleaseAll()
{
    RenderGL* pRender;

    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        for (auto Iterator = renderGLList[Layer].begin(); Iterator != renderGLList[Layer].end();)
        {
            pRender = (*Iterator);

            // リストから切り離す
            Iterator = renderGLList[Layer].erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pRender);
        }

        renderGLList[Layer].clear();
    }
}

/*===============================================================================================* 
  @Summary: 各レイヤーのRenderをカメラからの距離によってソートする
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::ZSort()
{
    for (int Layer = 0; Layer < GameObject::LAYER_MAX; ++Layer)
    {
        // 不透明はZDepth値はカメラから近い順にソートし、半透明は遠い順にソート
        if (Layer < GameObject::LAYER::OBJECT3D_TRANSLUCENT_ONE)
        {
            renderGLList[Layer].sort(RenderGL::ZSortCompareLess);
        }
        else
        {
            renderGLList[Layer].sort(RenderGL::ZSortCompareGreater);
        }
    }
}

/*===============================================================================================* 
  @Summary: 各レイヤーのRenderのZDepthの値を計算する
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::CalculateZSortAll()
{
    for (int Cnt = 0; Cnt < GameObject::LAYER_MAX; ++Cnt)
    {
        for (auto Iterator = renderGLList[Cnt].begin(); Iterator != renderGLList[Cnt].end(); ++Iterator)
        {
            
        }
    }
}

/*===============================================================================================*
  @Summary: Renderをリストに追加する
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::LinkList(RenderGL* pRender, GameObject::LAYER Layer)
{
    renderGLList[Layer].push_back(pRender);
}

/*===============================================================================================*
  @Summary: Renderをリストから解除する
  @Details: None
 *===============================================================================================*/
void RenderManagerGL::UnLinkList(RenderGL* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = renderGLList[Layer].begin(); Iterator != renderGLList[Layer].end(); ++Iterator)
    {
        if (*Iterator == pRender)
        {
            // リストから切り離す
            renderGLList[Layer].erase(Iterator);

            break;
        }
    }
}

/*===============================================================================================*
  @Summary: 対象のRenderを削除する (リストからも取り除く)
  @Details: 対象のRenderのUninit()が呼ばれる
 *===============================================================================================*/
void RenderManagerGL::Release(RenderGL* pRender)
{
    GameObject::LAYER Layer = pRender->GetLayer();

    for (auto Iterator = renderGLList[Layer].begin(); Iterator != renderGLList[Layer].end();)
    {
        if (*Iterator == pRender)
        {
            // リストから切り離す
            Iterator = renderGLList[Layer].erase(Iterator);

            // GameObjectの削除
            SafeDeleteUninit(pRender);

            return;
        }

        ++Iterator;
    }
}

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//