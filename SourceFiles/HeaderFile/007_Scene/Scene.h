/**************************************************************************************************

 @File   : [ Scene.h ] 画面遷移するシーンの基礎クラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----MainSetting-----//
#include "001_Manager/Manager.h"

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
class SceneTitle;
class SceneGame;
class SceneResult;

class Scene
{
public:
             Scene() {}
    virtual ~Scene() {}

    virtual void Init()   = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;

    virtual std::string GetSceneName() = 0;

    static SceneTitle  TITLE;
    static SceneGame   GAME;
    static SceneResult RESULT;
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//