#include "DeathStopEC.h"
#include "ComponentsManager.h"
#include "DeathControllerC.h"
#include "Entity.h"
#include "FactoriesFactory.h"
#include "Factory.h"
#include "RigidbodyPC.h"
#include "Scene.h"
#include <iostream>
#include <json.h>

void DeathStopEC::checkEvent() {
    Entity* player = scene_->getEntityById("Player");
    auto* rigid =
        reinterpret_cast<RigidbodyPC*>(player->getComponent("RigidbodyPC"));
    if (rigid->getLinearVelocity().y <= 0)
        reinterpret_cast<DeathControllerC*>(
            scene_->getEntityById("GameManager")
                ->getComponent("DeathControllerC"))
            ->playerDeath();
}

void DeathStopEC::destroy() {
    setActive(false);
    scene_->getComponentsManager()->eraseEC(this);
}

DeathStopECFactory::DeathStopECFactory() = default;

Component* DeathStopECFactory::create(Entity* _father, Json::Value& _data,
                                      Scene* _scene) {
    DeathStopEC* deathStop = new DeathStopEC();
    _scene->getComponentsManager()->addEC(deathStop);

    deathStop->setFather(_father);
    deathStop->setScene(_scene);

    deathStop->setActive(true);

    return deathStop;
};

DEFINE_FACTORY(DeathStopEC)
