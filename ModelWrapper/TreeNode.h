#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace ModelWrapper
{
	public ref class TreeNode
	{
	public:
		TreeNode();
		TreeNode(int value);
		!TreeNode();
		virtual ~TreeNode();

		void AddChild(TreeNode^ node);
		void RemoveChild(TreeNode^ node);

		void Save(String^ fileName);
		static TreeNode^ Open(String^ fileName);

		property int Value
		{
			int get() { return m_pNode->GetValue(); }
			void set(int value) { m_pNode->SetValue(value); }
		}

		property TreeNode^ Parent
		{
			TreeNode^ get() { return m_parent; }
		}

		property List<TreeNode^>^ Children
		{
			List<TreeNode^>^ get() { return m_children; }
		}

	private:
		TreeNode(Model::TreeNode* pNode, TreeNode^ parent);
		void Init(int value);

		Model::TreeNode* m_pNode;
		TreeNode^ m_parent;
		List<TreeNode^>^ m_children;
	};
}

