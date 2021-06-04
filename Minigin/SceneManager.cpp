#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void boop::SceneManager::FixedUpdate()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->FixedUpdate();
	}
}

void boop::SceneManager::Update()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->Update();
	}
}

void boop::SceneManager::LateUpdate()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->LateUpdate();
	}
}

void boop::SceneManager::Render()
{
	if (m_ActiveScene != nullptr)
	{
		m_ActiveScene->Render();
	}
}

boop::Scene& boop::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	if (m_Scenes.size() == 0)
	{
		m_ActiveScene = scene;
	}
	
	m_Scenes.push_back(scene);
	return *scene;
}
std::shared_ptr<boop::Scene> boop::SceneManager::GetScene(const std::string& name) const
{
	for (auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			return scene;
		}
	}
	return nullptr;
}
std::shared_ptr<boop::Scene> boop::SceneManager::GetActiveScene() const
{
	return m_ActiveScene;
}

void boop::SceneManager::SetSceneAsActive(const std::string& name)
{
	m_ActiveScene = GetScene(name);
}
void boop::SceneManager::SetSceneAsActive(std::shared_ptr<boop::Scene> scene)
{
	m_ActiveScene = scene;
}
