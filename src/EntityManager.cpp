#include "EntityManager.hpp"

EntityManager &EntityManager::instance()
{
	static EntityManager	*instance = new EntityManager;

	return (*instance);
}

std::shared_ptr<GameEntity> EntityManager::createEntity(const std::string name, const std::string filepath)
{
	entities.try_emplace(name, std::make_shared<GameEntity>(name));
	if (!filepath.empty())
	{
		entities.at(name)->addSpriteComponent2D(filepath);
		entities.at(name)->setPosition(std::rand() % 400, std::rand() % 400);
	}
	return (entities.at(name));
}

const std::shared_ptr<GameEntity> EntityManager::getEntity(const std::string name) const
{
	return (entities.at(name));
}

void EntityManager::renderAll(sf::RenderWindow &ref)
{
	for (auto& ent : entities)
	{
		auto temp = ent.second;
		temp->render(ref);
	}
}

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}
