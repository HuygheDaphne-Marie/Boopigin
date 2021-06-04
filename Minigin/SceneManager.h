#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>

namespace boop
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		[[nodiscard]] std::shared_ptr<Scene> GetScene(const std::string& name) const;
		[[nodiscard]] std::shared_ptr<Scene> GetActiveScene() const;

		void SetSceneAsActive(const std::string& name);
		void SetSceneAsActive(std::shared_ptr<boop::Scene> scene);

		void FixedUpdate();
		void Update();
		void LateUpdate();
		
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		std::shared_ptr<Scene> m_ActiveScene;
	};
}
