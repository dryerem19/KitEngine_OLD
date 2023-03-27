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
    for (auto [entity, player, transform, camera] :
        registry.view<PlayerComponent, TransformComponent, CameraComponent>().each())
    {
        processKeyboardMovement(player, transform, camera);
        processMouseMovement(player, transform, camera, deltaTime);
        updateCamera(camera, transform);
    }
}

void PlayerControllerSystem::processKeyboardMovement(const PlayerComponent& player,
    TransformComponent& transform, const CameraComponent& camera)
{
    glm::vec3 forward = camera.getForward();
    glm::vec3 right   = camera.getRight();

    // Перемещение вперед
    if (Input::GetKey(KeyCode::W)) {
        transform.mPosition += player.mMovementSpeed * forward;
    }
    
    // Перемещение назад
    if (Input::GetKey(KeyCode::S)) {
        transform.mPosition -= player.mMovementSpeed * forward;
    }

    // Перемещение влево
    if (Input::GetKey(KeyCode::A)) {
        transform.mPosition -= player.mMovementSpeed * right;
    }

    // Перемещение вправо
    if (Input::GetKey(KeyCode::D)) {
        transform.mPosition += player.mMovementSpeed * right;
    }
}

void PlayerControllerSystem::processMouseMovement(const PlayerComponent &player,
    TransformComponent &transform, CameraComponent &camera, const float& deltaTime)
{
    // Определяем в какую сторону нужно повернуть камеру
    float sign    = glm::sign(camera.getUp().y);

    // Вычисляем углы поворота в зависимости от ввода мыши и чувствительности
    glm::vec2 delta = Input::GetMouseDelta() * deltaTime * player.mMouseSensitivity;
    camera.mYaw   += sign * delta.x;
    camera.mPitch += delta.y;

    // Ограничение угла поворота вокруг горизонтальной оси в диапазоне от -90 до 90 градусов
    camera.mPitch = glm::clamp(camera.mPitch, -90.0f, 90.0f);
}

void PlayerControllerSystem::updateCamera(CameraComponent &camera, TransformComponent& transform)
{
    // Обновляем матрицу вида
    camera.mViewMatrix = glm::translate(glm::mat4(1.0f), transform.mPosition) * glm::toMat4(camera.getOrientation());
    camera.mViewMatrix = glm::inverse(camera.mViewMatrix);

    // Обновляем матрицу проекции
    float aspect = 1.0f;
    if (camera.mViewportWidth > 0 && camera.mViewportHeight > 0) {
        aspect = camera.mViewportWidth / camera.mViewportHeight;
    }
    camera.mProjMatrix = glm::perspective(glm::radians(camera.mFov), aspect, camera.mNearPlane, camera.mFarPlane);

    // Обновляем матрицу вида-проекции
    camera.mViewProjMatrix = camera.mProjMatrix * camera.mViewMatrix;
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