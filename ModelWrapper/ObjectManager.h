#pragma once

using namespace System;
using namespace System::Collections::Generic;

namespace ModelWrapper
{
	ref class TreeNode;

	public ref class ObjectManager
	{
	public:
		ObjectManager();
		virtual ~ObjectManager();

		virtual TreeNode^ GetObject(Model::TreeNode* pNode);
		virtual void Remove(TreeNode^ node);

	internal:
		virtual void Destroy();
		void Clear();

	private:
		Dictionary<IntPtr, TreeNode^>^ m_objectMap;
	};
};
