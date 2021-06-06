#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace boop;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name, unsigned int id)
	: m_Name(name)
	, m_Id(id)
{}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object, const unsigned int depth)
{
	const auto& findResult = m_ObjectsToAdd.find(depth);
	if (findResult == m_ObjectsToAdd.end())
	{
		m_ObjectsToAdd[depth] = std::vector<std::shared_ptr<GameObject>>{};
	}
	m_ObjectsToAdd[depth].push_back(object);
}

void Scene::Remove(const GameObject* object)
{
	for (auto& gameObject : m_Objects)
	{
		if (gameObject.get() == object)
		{
			Remove(gameObject);
			return;
		}
	}
}

void Scene::Remove(std::shared_ptr<GameObject>& object)
{
	object->MarkForDelete();
}

void Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}
void Scene::Update()
{
	//if (IsFirstUpdate)
	//{
	//	for (auto& object : m_Objects)
	//	{
	//		object->Startup();
	//	}
	//	IsFirstUpdate = false;
	//}
	
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}
void Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}
void Scene::Render() const
{
	//for (const auto& object : m_Objects)
	//{
	//	object->Render();
	//}
	for (auto& pair : m_ObjectsByDepth)
	{
		for (auto& gameObject : pair.second)
		{
			gameObject->Render();
		}
	}
}

void Scene::DeleteRemovedObjects()
{
	//for (int index = 0; index < m_Objects.size(); index++)
	//{
	//	if (m_Objects[index]->IsMarkedForDelete())
	//	{
	//		m_Objects[index] = m_Objects[m_Objects.size() - 1];
	//		m_Objects.pop_back();
	//		index--;
	//	}
	//}
	DeleteRemovedObjectsFromVector(m_Objects);
	for (auto& pair : m_ObjectsByDepth)
	{
		DeleteRemovedObjectsFromVector(pair.second);
	}
}

void Scene::DeleteRemovedObjectsFromVector(std::vector<std::shared_ptr<GameObject>>& vectorToRemoveFrom)
{
	for (int index = 0; index < vectorToRemoveFrom.size(); index++)
	{
		if (vectorToRemoveFrom[index]->IsMarkedForDelete())
		{
			vectorToRemoveFrom[index] = vectorToRemoveFrom[vectorToRemoveFrom.size() - 1];
			vectorToRemoveFrom.pop_back();
			index--;
		}
	}
}

void Scene::AddObjects()
{
	for (auto& pair : m_ObjectsToAdd)
	{
		for (auto& gameObject : pair.second)
		{
			m_Objects.push_back(gameObject);
			m_ObjectsByDepth[pair.first].push_back(gameObject);
		}
	}
	m_ObjectsToAdd.clear();
}

std::string Scene::GetName() const
{
	return m_Name;
}

unsigned Scene::GetId() const
{
	return m_Id;
}

