#pragma once
namespace boop
{
	class SceneObject // This seems like a good start for an actual GameObject class
	{
	public:
		virtual void FixedUpdate() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		
		virtual void Render() const = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
