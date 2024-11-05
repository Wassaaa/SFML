#ifndef ENTITYMANAGER_HPP
# define ENTITYMANAGER_HPP
# include <iostream>
# include <unordered_map>
# include <memory>
# include "GameEntity.hpp"

class EntityManager
{
	public:
		static EntityManager& instance();

		std::shared_ptr<GameEntity> createEntity(const std::string name, const std::string filepath = "");
		const std::shared_ptr<GameEntity> getEntity(const std::string name) const;
		void renderAll(sf::RenderWindow &ref);

	private:
		EntityManager();
		~EntityManager();

		std::unordered_map<std::string, std::shared_ptr<GameEntity>> entities;

};

#endif
