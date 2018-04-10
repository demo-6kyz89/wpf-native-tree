#include "stdafx.h"
#include "TreeNode.h"

const int NODE_INDEX_SIZE = 4;
const int NODE_VALUE_SIZE = 4;
const int NODE_ROOT_INDEX = -1;

USING_MODELNAMESPACE

TreeNode::TreeNode()
{
	Clear();
	m_value = 0;
}

TreeNode::TreeNode(int value)
{
	Clear();
	m_value = value;
}

TreeNode::~TreeNode()
{
	TreeNode* node = m_firstChild;
	while (node != NULL)
	{
		TreeNode* forDeletion = node;
		node = node->m_nextSibling;
		delete forDeletion;
	}
}

void TreeNode::Clear()
{
	m_parent = NULL;
	m_firstChild = NULL;
	m_lastChild = NULL;
	m_prevSibling = NULL;
	m_nextSibling = NULL;
}


int TreeNode::GetValue()
{
	return m_value;
}

void TreeNode::SetValue(int value)
{
	m_value = value;
}

TreeNode* TreeNode::GetParent()
{
	return m_parent;
}

TreeNode* TreeNode::GetFirstChild()
{
	return m_firstChild;
}

TreeNode* TreeNode::GetLastChild()
{
	return m_lastChild;
}

TreeNode* TreeNode::GetPrevSibling()
{
	return m_prevSibling;
}

TreeNode* TreeNode::GetNextSibling()
{
	return m_nextSibling;
}


void TreeNode::AddChild(TreeNode* node)
{
	node->m_parent = this;
	if (m_firstChild == NULL)
		m_firstChild = node;
	else
	{
		TreeNode* prevSibling = m_lastChild == NULL ? m_firstChild : m_lastChild;
		prevSibling->m_nextSibling = node;
		node->m_prevSibling = prevSibling;
		m_lastChild = node;
	}
}

void TreeNode::RemoveChild(TreeNode* node)
{
	if (node == m_firstChild)
		m_firstChild = node->m_nextSibling;
	else if (node == m_lastChild)
		m_lastChild = node->m_prevSibling;

	if (node->m_prevSibling != NULL)
		node->m_prevSibling->m_nextSibling = node->m_nextSibling;
	if (node->m_nextSibling != NULL)
		node->m_nextSibling->m_prevSibling = node->m_prevSibling;
	node->m_parent = NULL;
	node->m_prevSibling = NULL;
	node->m_nextSibling = NULL;
}


void TreeNode::Serialize(const wchar_t* fileName)
{
	std::ofstream file(fileName, std::ofstream::binary);
	int nodeIndex = 0;
	std::map<TreeNode*, int> mapIndex;
	Serialize(file, mapIndex, nodeIndex);
	file.close();
}

void TreeNode::Serialize(std::ofstream& file, std::map<TreeNode*, int>& mapIndex, int& nodeIndex)
{
	int parentIndex = NODE_ROOT_INDEX;
	if (m_parent != NULL)
		parentIndex = mapIndex[m_parent];
	file.write(reinterpret_cast<const char *>(&parentIndex), NODE_INDEX_SIZE);
	file.write(reinterpret_cast<const char *>(&m_value), NODE_VALUE_SIZE);
	mapIndex[this] = nodeIndex++;

	TreeNode* node = m_firstChild;
	while (node != NULL)
	{
		node->Serialize(file, mapIndex, nodeIndex);
		node = node->m_nextSibling;
	}
}

TreeNode* TreeNode::Deserialize(const wchar_t* fileName)
{
	TreeNode* root = NULL;
	std::map<int, TreeNode*> mapNode;
	std::ifstream file(fileName, std::ifstream::binary);
	int nodeIndex = 0;
	while (true)
	{
		int parentIndex = 0;
		int value = 0;
		file.read(reinterpret_cast<char *>(&parentIndex), NODE_INDEX_SIZE);
		file.read(reinterpret_cast<char *>(&value), NODE_VALUE_SIZE);
		if (file.eof())
			break;

		TreeNode* node = new TreeNode(value);
		if (parentIndex == NODE_ROOT_INDEX)
			root = node;
		else
		{
			TreeNode* parentNode = mapNode[parentIndex];
			parentNode->AddChild(node);
		}
		mapNode[nodeIndex++] = node;
	}
	return root;
}

