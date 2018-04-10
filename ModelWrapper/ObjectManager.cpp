#include "stdafx.h"
#include "ObjectManager.h"
#include "TreeNode.h"

using namespace ModelWrapper;

ObjectManager::ObjectManager()
{
	m_objectMap = gcnew Dictionary<IntPtr, TreeNode^>();
}

ObjectManager::~ObjectManager()
{
	Destroy();
}

void ObjectManager::Destroy()
{
	if (m_objectMap != nullptr)
	{
		Clear();
		delete m_objectMap;
		m_objectMap = nullptr;
	}
}

void ObjectManager::Clear()
{
	for each (KeyValuePair<System::IntPtr, TreeNode^> kvp in m_objectMap)
		delete kvp.Value;

	m_objectMap->Clear();
}

void ObjectManager::Remove(TreeNode^ node)
{
	if (node == nullptr || m_objectMap == nullptr)
		return;

	Model::TreeNode *pNode = node->GetNode();
	if (!pNode)
		return;

	m_objectMap->Remove((IntPtr)pNode);

	if (node->Children != nullptr)
	{
		int i = node->Children->Count - 1;
		for (; i >= 0; i--)
			Remove(node->Children[i]);
	}

	node->ClearNode();
}

TreeNode^ ObjectManager::GetObject(Model::TreeNode* pNode)
{
	if (pNode == NULL)
		return nullptr;

	TreeNode^ node = nullptr;
	if (m_objectMap->TryGetValue((IntPtr)pNode, obj))
		return node;

	node = gcnew TreeNode();
	node->Attach(pNode);
	node->ObjManager = this;

	m_objectMap[(IntPtr)pNode] = node;

	return node;
}
