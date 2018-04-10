#include "stdafx.h"
#include "TreeNode.h"

using namespace ModelWrapper;

TreeNode::TreeNode()
{
	Init(0);
}

TreeNode::TreeNode(int value)
{
	Init(value);
}

void TreeNode::Init(int value)
{
	m_pNode = new Model::TreeNode(value);
	m_parent = nullptr;
	m_children = gcnew List<TreeNode^>();
}

TreeNode::TreeNode(Model::TreeNode* pNode, TreeNode^ parent)
{
	m_pNode = pNode;
	m_parent = parent;
	m_children = gcnew List<TreeNode^>();
	Model::TreeNode* pChild = pNode->GetFirstChild();
	while (pChild != NULL)
	{
		TreeNode^ child = gcnew TreeNode(pChild, this);
		m_children->Add(child);
		pChild = pChild->GetNextSibling();
	}
}

TreeNode::!TreeNode()
{
	if (m_pNode != NULL)
	{
		if (m_pNode->GetParent() == NULL)
			delete m_pNode;
		m_pNode = NULL;
	}
}

TreeNode::~TreeNode()
{
	m_parent = nullptr;
	if (m_children != nullptr)
	{
		delete m_children;
		m_children = nullptr;
	}
	this->!TreeNode();
}


void TreeNode::AddChild(TreeNode^ node)
{
	node->m_parent = this;
	m_children->Add(node);
	m_pNode->AddChild(node->m_pNode);
}

void TreeNode::RemoveChild(TreeNode^ node)
{
	node->m_parent = nullptr;
	m_children->Remove(node);
	m_pNode->RemoveChild(node->m_pNode);
}


void TreeNode::Save(String^ fileName)
{
	wchar_t* pFileName = (wchar_t*)Marshal::StringToHGlobalUni(fileName).ToPointer();
	m_pNode->Serialize(pFileName);
}

TreeNode^ TreeNode::Open(String^ fileName)
{
	wchar_t* pFileName = (wchar_t*)Marshal::StringToHGlobalUni(fileName).ToPointer();
	Model::TreeNode* pNode = Model::TreeNode::Deserialize(pFileName);
	return gcnew TreeNode(pNode, nullptr);
}
