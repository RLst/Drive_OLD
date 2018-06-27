#pragma once
#include <vector>
#include <Matrix3.h>

namespace aie {
	class Renderer2D;
}

class SceneObject
{
protected:
	SceneObject*				m_parent = nullptr;
	std::vector<SceneObject*>	m_children;

	//Transforms
	Matrix3			m_localTrans = Matrix3::identity;
	Matrix3			m_worldTrans = Matrix3::identity;

public:
	SceneObject();
	virtual ~SceneObject();

	//Graph functions
	void			addChild(SceneObject* child);			//Add
	void			removeChild(SceneObject* child);		//Remove

	SceneObject*	getChild(size_t index) const;
	SceneObject*	getParent() const;
	size_t			childCount() const;

	//Updates and Draws
	virtual void	onUpdate(float deltaTime) {};			//To be overwritten by child classes
	virtual void	onDraw(aie::Renderer2D* renderer) {};	//To be overwritten by child classes

	void			update(float deltaTime);
	void			draw(aie::Renderer2D* renderer);

	void			updateTransform();

	//Get transforms
	Matrix3			getWorldTrans() const { return m_worldTrans; }
	Matrix3			getLocalTrans() const { return m_localTrans; }
	
	//Manipulate local transform
	void			setPosition(float x, float y);
	void			setPosition(const Vector3 &vec);

	void			translate(float x, float y);
	void			translate(const Vector3 &vec);

	void			setRotate(float radians);
	void			rotate(float radians);

	void			setScale(float width, float height);
	void			scale(float width, float height);
};

