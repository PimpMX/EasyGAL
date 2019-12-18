#include "Node.h"

#pragma warning ( disable: 26812 )

Node::Node()
{
	m_pValue = nullptr;
	m_Value = VALUE_NONE;

	m_pParent = nullptr;
	m_Children.first = nullptr;
	m_Children.second = nullptr;
}

Node::~Node()
{
	delete m_Children.first;
	delete m_Children.second;
}

Node::Node(Node* pParent)
{
	m_pValue = nullptr;
	m_Value = VALUE_NONE;

	m_pParent = pParent;
	m_Children.first = nullptr;
	m_Children.second = nullptr;
}

bool Node::IsLeaf()
{
	return !m_Children.first && !m_Children.second;
}

bool Node::IsRoot()
{
	return !m_pParent;
}

/* If m_pValue is set Node::GetValue() will return parent value else it will return its own value */

NodeValue Node::GetValue()
{
	if (!m_pValue)
		return m_Value;
	else
		return (NodeValue)(*m_pValue);
}

void Node::SetValue(bool* pValue)
{
	if (pValue)
		m_pValue = pValue;
}

void Node::SetValue(NodeValue Value)
{
	m_Value = Value;
}

Node* Node::GetParent()
{
	return m_pParent;
}

Node* Node::GetLeft()
{
	return m_Children.first;
}

Node* Node::GetRight()
{
	return m_Children.second;
}

void Node::SetParent(Node* pParent)
{
	m_pParent = pParent;
}

void Node::SetLeft(Node* pLeft)
{
	m_Children.first = pLeft;
}

void Node::SetRight(Node* pRight)
{
	m_Children.second = pRight;
}

Node* Node::InsertLeft()
{
	m_Children.first = new Node(this);
	return m_Children.first;
}

Node* Node::InsertRight()
{
	m_Children.second = new Node(this);
	return m_Children.second;
}
