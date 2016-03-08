/**************************************************************************************************

 @File   : [ Transform.cpp ] オブジェクトの位置、回転、スケールを扱うクラス
 @Auther : Unisawa

**************************************************************************************************/



//***********************************************************************************************//
//                                                                                               //
//  @Include File                                                                                //
//                                                                                               //
//***********************************************************************************************//

//-----Object-----//
#include "004_Component/0042_GameObject/Transform.h"
#include "004_Component/0042_GameObject/GameObjectManager.h"

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
const std::string Transform::className = "Transform";

/*=================================================================================================
  @Summary: コンストラクタ
  @Details: None
=================================================================================================*/
Transform::Transform(GameObject* pObject) : Component(pObject, TRANSFORM, className)
{
    parent = NULL;

    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 0.0f;

    rotation.x = 0.0f;
    rotation.y = 0.0f;
    rotation.z = 0.0f;

    lossyScale.x = 1.0f;
    lossyScale.y = 1.0f;
    lossyScale.z = 1.0f;

    gameObject = pObject;
    transform  = this;
}

/*===============================================================================================* 
  @Summary: デストラクタ
  @Details: None
 *===============================================================================================*/
Transform::~Transform()
{

}

/*===============================================================================================* 
  @Summary: ワールド行列の生成
  @Details: None
 *===============================================================================================*/
void Transform::CreateWorldMatrix()
{
    // ワールドマトリックスの初期化
    worldMatrix.Identity();

    // Rot
    worldMatrix.SetRotateYawPitchRoll(rotation);

    // Scale
    worldMatrix.SetScaling(lossyScale);

    // position
    worldMatrix.SetTranslate(position);

    // 親が存在すれば、親のワールド行列を掛ける
    if (this->parent != NULL)
    {
        worldMatrix *= this->parent->transform->worldMatrix;
    }
}

/*===============================================================================================* 
  @Summary: 対象の親オブジェクトの子かどうか判定する。
  @Details: True なら valueの子に自身が存在する。
 *===============================================================================================*/
bool Transform::IsChildOf(Transform* value)
{
    for (auto Iterator = value->childrentList.begin(); Iterator != value->childrentList.end();)
    {
        if ((*Iterator) == this)
        {
            return true;
        }

        Iterator++;
    }

    return false;
}

/*===============================================================================================* 
  @Summary: 親オブジェクトから自身を切り離す
  @Details: pGameObject が親のオブジェクト
 *===============================================================================================*/
void Transform::DetachParent()
{
    if (this->parent == NULL) return;

    GameObject* pGameObject;

    for (auto Iterator = this->parent->childrentList.begin(); Iterator != this->parent->childrentList.end();)
    {
        pGameObject = (*Iterator)->gameObject;

        if (pGameObject == this->gameObject)
        {
            // リストから切り離す
            this->parent->childrentList.erase(Iterator);

            // リスト登録
            GameObjectManager::LinkList(this->gameObject, this->gameObject->GetLayer());

            // 親のTransformを自分に反映させる
            Matrix TransMatrix;
            TransMatrix.SetTranslate(this->transform->GetPosition());
            TransMatrix *= this->parent->GetWorldMatrix();
            this->SetPosition(TransMatrix._41, TransMatrix._42, TransMatrix._43);
            this->rotation += this->transform->parent->rotation;
            //for (Transform *pParent = pGameObject->transform->parent; pParent != NULL;)
            //{
            //    this->rotation += pParent->rotation;
            //    pParent = pParent->parent;
            //}

            this->transform->parent = NULL;

            return;
        }

        Iterator++;
    }
}

/*===============================================================================================* 
  @Summary: 対象の子オブジェクトを親オブジェクト(自身)から切り離す
  @Details: None
 *===============================================================================================*/
void Transform::DetachChildren(Transform* value)
{
    GameObject* pGameObject;

    for (auto Iterator = this->childrentList.begin(); Iterator != this->childrentList.end();)
    {
        pGameObject = (*Iterator)->gameObject;

        if (pGameObject == value->gameObject)
        {
            // リスト登録
            GameObjectManager::LinkList(pGameObject, pGameObject->GetLayer());

            // リストから切り離す
            this->childrentList.erase(Iterator);

            // 親のTransformを自分に反映させる
            Matrix TransMatrix;
            TransMatrix.SetTranslate(pGameObject->transform->GetPosition());
            TransMatrix *= pGameObject->transform->parent->GetWorldMatrix();
            pGameObject->transform->SetPosition(TransMatrix._41, TransMatrix._42, TransMatrix._43);
            pGameObject->transform->rotation += this->rotation;
            //for (Transform *pParent = this->parent; pParent != NULL;)
            //{
            //    pGameObject->transform->rotation -= pParent->rotation;
            //    pParent = pParent->parent;
            //}

            pGameObject->transform->parent = NULL;

            return;
        }

        Iterator++;
    }
}

/*===============================================================================================* 
  @Summary: 全ての子オブジェクトを親オブジェクト(自身)から切り離す
  @Details: None
 *===============================================================================================*/
void Transform::DetachChildrenAll()
{
    GameObject* pGameObject;

    for (auto Iterator = this->childrentList.begin(); Iterator != this->childrentList.end();)
    {
        pGameObject = (*Iterator)->gameObject;

        // リスト登録
        GameObjectManager::LinkList(pGameObject, pGameObject->GetLayer());

        // 親のTransformを自分に反映させる
        Matrix TransMatrix;
        TransMatrix.SetTranslate(pGameObject->transform->GetPosition());
        TransMatrix *= pGameObject->transform->parent->GetWorldMatrix();
        pGameObject->transform->SetPosition(TransMatrix._41, TransMatrix._42, TransMatrix._43);
        pGameObject->transform->rotation += this->rotation;
        //for (Transform *pParent = this->parent; pParent != NULL;)
        //{
        //    pGameObject->transform->rotation -= pParent->rotation;
        //    pParent = pParent->parent;
        //}

        pGameObject->transform->parent = NULL;

        Iterator++;
    }

    childrentList.clear();
}

/*===============================================================================================* 
  @Summary: 指定したオブジェクトを親としてこのGameObjectに設定する
  @Details: None
 *===============================================================================================*/
void Transform::SetParent(Transform* value)
{
    // 既に親の子になっている場合、終了
    if (this->IsChildOf(value)) return;

    value->childrentList.push_back(this);
    GameObjectManager::UnLinkList(this->gameObject);    // 親のUpdate()内で子のUpdateを呼ぶため自身をリストから外す
    this->parent = value;

    // 親のTransformを自分に反映させる
    Matrix TransMatrix, InverseMatrix;
    TransMatrix.SetTranslate(this->position);
    InverseMatrix = value->worldMatrix.Inverse();
    if (InverseMatrix != Matrix::zero)
    {
        Matrix ReturnMatrix = TransMatrix * InverseMatrix;
        this->SetPosition(ReturnMatrix._41, ReturnMatrix._42, ReturnMatrix._43);
        this->rotation -= value->rotation;
    }
}

/*===============================================================================================* 
  @Summary: 指定したオブジェクトを子としてこのGameObjectに設定する
  @Details: None
 *===============================================================================================*/
void Transform::SetChild(Transform* value)
{
    // 既に親の子になっている場合、終了
    if (value->IsChildOf(this)) return;

    this->childrentList.push_back(value);
    GameObjectManager::UnLinkList(value->gameObject);    // 親のUpdate()内で子のUpdateを呼ぶため自身をリストから外す
    value->parent = this;

    // 親のTransformを自分に反映させる
    Matrix TransMatrix, InverseMatrix;
    TransMatrix.SetTranslate(value->position);
    InverseMatrix = this->worldMatrix.Inverse();
    if (InverseMatrix != Matrix::zero)
    {
        Matrix ReturnMatrix = TransMatrix * InverseMatrix;
        value->SetPosition(ReturnMatrix._41, ReturnMatrix._42, ReturnMatrix._43);
        value->rotation -= this->rotation;
        //for (Transform *pParent = this->parent; pParent != NULL;)
        //{
        //    value->rotation += pParent->rotation;
        //    pParent = pParent->parent;
        //}
    }
}

/*===============================================================================================* 
  @Summary: 
  @Details: 
 *===============================================================================================*/

//===============================================================================================//
//                                                                                               //
//                                          @End of File                                         //
//                                                                                               //
//===============================================================================================//
