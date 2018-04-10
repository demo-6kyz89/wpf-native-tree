#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ModelUnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(ModelCreate)
		{
			Model::TreeNode* node = CreateTestModel();
			Assert::IsNotNull(node);
			delete node;
		}

		TEST_METHOD(ModelRemoveFirstChild)
		{
			Model::TreeNode* node = CreateTestModel();
			Model::TreeNode* firstChild = node->GetFirstChild();
			node->RemoveChild(firstChild);
			Assert::IsNull(firstChild->GetParent());
			delete firstChild;
			delete node;
		}

		TEST_METHOD(ModelSerialization)
		{
			const wchar_t* fileName = L"model.bin";
			Model::TreeNode* node = CreateTestModel();
			node->Serialize(fileName);
			Model::TreeNode* node1 = Model::TreeNode::Deserialize(fileName);
			Assert::IsTrue(node->GetValue() == node1->GetValue());
			Assert::IsTrue(node->GetFirstChild()->GetValue() == node1->GetFirstChild()->GetValue());
			Assert::IsTrue(node->GetLastChild()->GetValue() == node1->GetLastChild()->GetValue());
			delete node;
			delete node1;
		}

	private:
		Model::TreeNode* CreateTestModel()
		{
			Model::TreeNode* root = new Model::TreeNode(4);

			Model::TreeNode* node1 = new Model::TreeNode(8);
			root->AddChild(node1);

			Model::TreeNode* node11 = new Model::TreeNode(7);
			node1->AddChild(node11);

			Model::TreeNode* node12 = new Model::TreeNode(1);
			node1->AddChild(node12);

			Model::TreeNode* node2 = new Model::TreeNode(2);
			root->AddChild(node2);

			Model::TreeNode* node21 = new Model::TreeNode(9);
			node2->AddChild(node21);

			return root;
		}

	};
}