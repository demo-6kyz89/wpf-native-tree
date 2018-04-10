#pragma once

#include "ModelLibrary.h"
#include <map>
#include <fstream>

BEGIN_MODELNAMESPACE

class MODEL_API TreeNode
{
public:
	TreeNode();
	TreeNode(int value);
	~TreeNode();

	int GetValue();
	void SetValue(int value);
	TreeNode* GetParent();
	TreeNode* GetFirstChild();
	TreeNode* GetLastChild();
	TreeNode* GetPrevSibling();
	TreeNode* GetNextSibling();

	void AddChild(TreeNode* node);
	void RemoveChild(TreeNode* node);

	void Serialize(const wchar_t* fileName);
	static TreeNode* Deserialize(const wchar_t* fileName);

private:
	void Clear();
	void Serialize(std::ofstream& file, std::map<TreeNode*, int>& mapIndex, int& nodeIndex);

	TreeNode* m_parent;
	TreeNode* m_firstChild;
	TreeNode* m_lastChild;
	TreeNode* m_prevSibling;
	TreeNode* m_nextSibling;
	int m_value;
};

END_MODELNAMESPACE
