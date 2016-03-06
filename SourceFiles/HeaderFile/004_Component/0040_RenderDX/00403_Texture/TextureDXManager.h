/**************************************************************************************************

 @File   : [ TextureDXManager.h ] TextureDXを管理するクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _TEXTUREDXMANAGER_H_
#define _TEXTUREDXMANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0040_RenderDX/00403_Texture/TextureDX.h"

//***********************************************************************************************//
//                                                                                               //
//  @Macro Definition                                                                            //
//                                                                                               //
//***********************************************************************************************//
#ifdef USE_DIRECTX

//***********************************************************************************************//
//                                                                                               //
//  @Class                                                                                       //
//                                                                                               //
//***********************************************************************************************//
class TextureDX;

class TextureDXManager
{
public:
     TextureDXManager() {}
    ~TextureDXManager() {}

    static TextureDXManager* Create();

    void Init();
    void Uninit();
    void Update();

    static TextureDX* CheckLoaded(const std::string TextureName);
    static TextureDX* Load(const std::string TextureName);

    static void Delete(unsigned int TextureID);

    static LPDIRECT3DTEXTURE9 GetTexture(unsigned int TextureID);

    static void UnLinkListAll();
    static void ReleaseAll();

    //-----Operation List-----//
    static void LinkList(TextureDX* pTextureDX);
    static void UnLinkList(TextureDX* pTextureDX);
    static void Release(TextureDX* pTextureDX);

private:
    static std::list<TextureDX*> pTextureDXList;
};
#endif

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
