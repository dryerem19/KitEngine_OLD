/**
 * @file PlayerControllerSystem.cpp
 * @author Denis Eremenko (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-07
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#include "pch.h"
#include "PlayerControllerSystem.h"
#include "Input.h"
#include "MathHelper.h"

PlayerControllerSystem::PlayerControllerSystem() { }

void PlayerControllerSystem::update(entt::registry &registry, float deltaTime)
{
    auto view = registry.view<PlayerComponent, TransformComponent, CameraComponent>();
    for (const auto entity : view)
    {
        // auto& player    = view.get<PlayerComponent>(entity);
        // auto& transform = view.get<TransformComponent>(entity);
        // auto& camera    = view.get<CameraComponent>(entity);

        // static glm::vec2 mOldMousePosition = Input::mousePosition;
        // glm::vec2 delta = (Input::mousePosition - mOldMousePosition) * 0.003f;
        // mOldMousePosition = Input::mousePosition;

        // updatePosition(transform, camera, player);
        // updateOrientation(transform, camera, player, delta);

        // camera.mView = glm::translate(glm::mat4(1.0f), transform.mPosition) * glm::toMat4(camera.orientation());
        // camera.mView = glm::inverse(camera.mView);

        // // Обновляем матрицу проекции
        // camera.mProj = glm::perspective(glm::radians(camera.mFov), camera.mAspect, camera.mNear, camera.mFar);

        // // Обновляем матрицу вида и проекции
        // camera.mViewProj = camera.mView * camera.mProj;

        //std::cout << transform.GetDebugInfo();

        //updateCameraPosition
    }
}

void PlayerControllerSystem::updatePosition(TransformComponent &transform, CameraComponent& camera, PlayerComponent &player)
{
    // if (Input::GetKey(KeyCode::W)) {
    //     camera.mPosition += player.mMovementSpeed * camera.getForward();
    // }
    // if (Input::GetKey(KeyCode::S)) {
    //     glm::vec3 forward = camera.getForward();
    //     camera.mPosition -= player.mMovementSpeed * forward;
    // }
    // if (Input::GetKey(KeyCode::A)) {
    //     camera.mPosition -= camera.getRight() * player.mMovementSpeed;
    // }
    // if (Input::GetKey(KeyCode::D)) {
    //     camera.mPosition += camera.getRight() * player.mMovementSpeed;
    // }
}

void PlayerControllerSystem::updateOrientation(TransformComponent &transform, CameraComponent& camera, PlayerComponent& player, glm::vec2 &delta)
{
    // float yawSign = camera.getUp().y < 0 ? -1.0f : 1.0f;
    // camera.mYaw += yawSign * delta.x * player.mMouseSensitivity;
    // camera.mPitch += delta.y * player.mMouseSensitivity;
}

// bool PlayerControllerSystem::checkIfGroundedRay(const RigidbodyComponent &rigidbodyComponent)
// {
//     /**
//      * Здесь мы проверяем, находится ли объект на земле, используя луч для определения
//      * наличия столкновений с объектами на нижней поверхности тела.
//      */
//     const btRigidBody* pBody = rigidbodyComponent.mRigidBody.get();

//     btVector3 origin = pBody->getWorldTransform().getOrigin();
//     btVector3 downDir = pBody->getWorldTransform().getBasis() * btVector3(0, -1, 0);

//     btScalar distance = m_stepHeight + 0.1; // добавляем дополнительный отступ
//     btCollisionWorld::ClosestRayResultCallback resultCallback(origin, origin + downDir * distance);
//     resultCallback.m_collisionFilterGroup = btBroadphaseProxy::DefaultFilter;
//     resultCallback.m_collisionFilterMask = btBroadphaseProxy::StaticFilter;
//     if (pBody->getMotionState()) {
//         resultCallback.m_collisionObject = pBody;
//     }

//     mDynamicsWorld.rayTest(origin, origin + downDir * distance, resultCallback);
//     return resultCallback.hasHit();
// }

bool PlayerControllerSystem::checkIfGroundedBruteforce(const RigidbodyComponent &rigidbodyComponent)
{
    /**
     * Здесь мы проходимся по всем контактным парам и ищем пару, в которой участвует проверяемый объект body.
     * Далее мы получаем нормаль контакта, используя метод getContactPoint(0).m_normalWorldOnB. Чтобы узнать,
     * с какой стороны контактная пара находится относительно проверяемого объекта body, мы проверяем, какой
     * из объектов равен body. Если объект obA равен body, то нормаль контакта направлена в сторону объекта obB
     * и её нужно инвертировать. Если же объект obB равен body, то нормаль уже направлена в нужную сторону.
    
     * Затем мы проверяем направление нормали по оси Y. Если нормаль направлена вниз (Y > 0.7), значит объект
     * касается земли и метод возвращает true. Если ни одна из контактных пар не удовлетворяет условию, то метод
     * возвращает false.
    */

    // const btRigidBody* pBody = rigidbodyComponent.mRigidBody.get();
    // const btScalar threshold = 0.7f;

    // // Перебираем все контактные пары
    // int numManifolds = mDynamicsWorld.getDispatcher()->getNumManifolds();
    // for (int i = 0; i < numManifolds; i++) 
    // {
    //     // Получаем объекты, участвующие в контакте
    //     btPersistentManifold* pContactManifold = mDynamicsWorld.getDispatcher()->getManifoldByIndexInternal(i);
    //     const btCollisionObject* pObjA = pContactManifold->getBody0();
    //     const btCollisionObject* pObjB = pContactManifold->getBody1();

    //     if ((pObjA == pBody || pObjB == pBody)) {
    //         btVector3 normal;
    //         if (pObjA == pBody) {
    //             normal -= -pContactManifold->getContactPoint(0).m_normalWorldOnB;
    //         } else {
    //             normal = pContactManifold->getContactPoint(0).m_normalWorldOnB;
    //         }

    //         if (normal.getY() > threshold) {
    //             return true;
    //         }
    //     }
    // }

    // return false;
}