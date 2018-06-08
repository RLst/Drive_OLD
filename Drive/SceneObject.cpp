#include "SceneObject.h"
#include <cassert>
#include <Vector3.h>

SceneObject::SceneObject()
{}

SceneObject::~SceneObject()
{
	//If the parent is not the root object then remove this child
	if (m_parent != nullptr)	
		m_parent->removeChild(this);
}
