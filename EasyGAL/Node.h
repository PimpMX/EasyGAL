#pragma once

#include <utility>

using namespace std;

enum NodeValue 
{
	VALUE_FALSE, 
	VALUE_TRUE,
	VALUE_NONE,
	OPERATOR_NOT,
	OPERATOR_AND,
	OPERATOR_OR,
	OPERATOR_XOR
};

class Node
{

public:

	Node();
	~Node();

	Node(Node* pParent);

	bool IsLeaf();
	bool IsRoot();

	NodeValue GetValue();

	void SetValue(bool* pValue);
	void SetValue(NodeValue Value);

	Node* GetParent();
	Node* GetLeft();
	Node* GetRight();

	void SetParent(Node* pParent);
	void SetLeft(Node* pLeft);
	void SetRight(Node* pRight);

	Node* InsertLeft();
	Node* InsertRight();

private:

	bool* m_pValue;
	NodeValue m_Value;

	Node* m_pParent;
	pair<Node*, Node*> m_Children;
};

