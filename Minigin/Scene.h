#pragma once
#include "SceneManager.h"
#include <map>

namespace boop
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object, unsigned int depth = 0);
		void Remove(const GameObject* object);
		void Remove(std::shared_ptr<GameObject>& object);

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void Render() const;

		void DeleteRemovedObjects();
		void DeleteRemovedObjectsFromVector(std::vector<std::shared_ptr<GameObject>>& vectorToRemoveFrom);
		void AddObjects();

		[[nodiscard]] std::string GetName() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;

		std::vector<std::shared_ptr<GameObject>> m_Objects{};
		std::map<unsigned int, std::vector<std::shared_ptr<GameObject>>> m_ObjectsByDepth{};
		std::map<unsigned int, std::vector<std::shared_ptr<GameObject>>> m_ObjectsToAdd{};
		
		static unsigned int m_IdCounter; 
	};

}
