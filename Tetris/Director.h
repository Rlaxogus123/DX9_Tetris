#pragma once
class Director : public Singleton<Director>
{
private:
	Scene* _currentScene;
public:
	void DirectorInit();
	void ChangeScene(Scene* s);
	void SceneUpdate();
};

