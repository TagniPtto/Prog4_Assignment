#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "FPSComponent.h"
#include "Scene.h"
#include "GameObject.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto gameObject = std::make_shared<dae::GameObject>();
	gameObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	auto text = gameObject->GetComponent<dae::TextComponent>(0);
	if (text != nullptr) {
		text->SetPosition(80, 20);
	}
	gameObject->AddComponent<dae::FPSComponent>("0", font);



	scene.Add(gameObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}