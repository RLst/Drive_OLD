#include "SceneObject.h"
#include <cassert>
#include <Vector3.h>
#include <Matrix3.h>

SceneObject::SceneObject()
{}

SceneObject::~SceneObject()
{
	//If the parent is not the root object then remove this child
	if (m_parent != nullptr)	
		m_parent->removeChild(this);
}

void SceneObject::addChild(SceneObject * child)
{
	//Make sure it doesn't have a parent already
	assert(child->m_parent == nullptr);
	//Assign "this" as parent
	child->m_parent = this;
	//Add new child to collection
	m_children.push_back(child);
}

void SceneObject::removeChild(SceneObject * child)
{
	//Find the child in the collection
	auto iter = std::find(m_children.begin(), m_children.end(), child);
	//If found, remove it
	if (iter != m_children.end()) {
		m_children.erase(iter);
		//Also unassign parent
		child->m_parent = nullptr;
	}
}

SceneObject * SceneObject::getChild(size_t index) const
{
	return m_children[index];
}

SceneObject * SceneObject::getParent() const
{
	return m_parent;
}

size_t SceneObject::childCount() const
{
	return m_children.size();
}

void SceneObject::update(float deltaTime)
{
	//Run onUpdate behaviour
	onUpdate(deltaTime);

	//Update children
	for (auto child : m_children)
		child->update(deltaTime);
}

void SceneObject::draw(aie::Renderer2D * renderer)
{
	//Run onDraw behaviour
	onDraw(renderer);

	//Draw children
	for (auto child : m_children)
		child->draw(renderer);
}

void SceneObject::updateTransform()
{
	//Update world transform
	if (m_parent != nullptr)
		m_worldTrans = m_parent->m_worldTrans * m_localTrans;
	else
		m_worldTrans = m_localTrans;

	//Update transform for all children
	for (auto child : m_children)
		child->updateTransform();
}

void SceneObject::setPosition(float x, float y)
{
	m_localTrans[2] = { x, y, 1 };
	updateTransform();
}

void SceneObject::setPosition(const Vector3 & vec)
{
	m_localTrans[2] = { vec.x, vec.y, 1 };
	updateTransform();
}

void SceneObject::setRotate(float radians)
{
	m_localTrans.setRotateZ(radians);
	updateTransform();
}

void SceneObject::setScale(float width, float height)
{
	m_localTrans.setScale(width, height, 1);
	updateTransform();
}

void SceneObject::translate(float x, float y)
{
	m_localTrans.translate(x, y);
	updateTransform();
}

void SceneObject::translate(const Vector3 & vec)
{
	m_localTrans.translate(vec.x, vec.y);
	updateTransform();
}

void SceneObject::rotate(float radians)
{
	m_localTrans.rotateZ(radians);
	updateTransform();
}

void SceneObject::scale(float width, float height)
{
	m_localTrans.scale(width, height, 1);
	updateTransform();
}
