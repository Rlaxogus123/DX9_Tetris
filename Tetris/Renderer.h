#pragma once
class Renderer : public Singleton<Renderer>
{
private:
	static bool Comp(Node* a, Node* b);
	list<Node*> _rendertargets;

public:
	void AddRenderTarget(Node* node);
	void DeleteRenderTarget(Node* node);
	void Render();
};

