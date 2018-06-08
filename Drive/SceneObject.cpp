#include "SceneObject.h"
#include <cassert>
#include <Vector3.h>

SceneObject::SceneObject()
{}

SceneObject::~SceneObject()
{
	//Detach from parent
	if (m_parent != nullptr)
		m_parent->removeChild(this);
}
