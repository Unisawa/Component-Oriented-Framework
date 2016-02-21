/**************************************************************************************************

 @File   : [ GameObjectManager.h ] ëSÇƒÇÃé¿ëÃÇä«óùÉNÉâÉX
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include Guard                                                                               //
//                                                                                               //
//***********************************************************************************************//
#pragma once
#ifndef _GAMEOBJECTMANAGER_H_
#define _GAMEOBJECTMANAGER_H_

//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0042_GameObject/GameObject.h"

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
class GameObjectManager
{
public:
     GameObjectManager() {}
    ~GameObjectManager() {}

    static GameObjectManager* Create();

    void Init();
    void Uninit();
    void Update();

    static void UpdateAll();
    static void DrawAll();
    static void ReleaseAll();
    static void ReleaseAllScene();

    static GameObject* FindGameObject(std::string Name);

    //-----Operation List-----//
    static void LinkList(GameObject* pObject, GameObject::LAYER Layer);
    static void UnLinkList(GameObject* pObject);
    static void Release(GameObject* pObject);

    static std::list<GameObject*>* GetGameObjectList() { return pGameObjectList; }

private:
    static std::list<GameObject*> pGameObjectList[GameObject::LAYER_MAX];
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//