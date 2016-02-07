/**************************************************************************************************

 @File   : [ GameObjectManager.h ] �S�Ă̎��̂��Ǘ��N���X
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

    //-----Operation List-----//
    static void LinkList(GameObject* pObject, GameObject::LAYER Layer);
    static void UnLinkList(GameObject* pObject);
    static void Release(GameObject* pObject);

private:
    static std::list<GameObject*> gameObjectList[GameObject::LAYER_MAX];
};

#endif
//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//