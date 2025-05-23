//#include <SDL.h>
//
//#if _DEBUG
//// ReSharper disable once CppUnusedIncludeDirective
//#if __has_include(<vld.h>)
//#include <vld.h>
//#endif
//#endif
//
//#include "Minigin.h"
//#include "SceneManager.h"
//#include "ResourceManager.h"
//
//#include "FPSComponent.h"
//#include "RenderComponent.h"
//#include "RotatorComponent.h"
//#include "ImGuiComponent.h"
//
//#include "Scene.h"
//#include "GameObject.h"
//
//
//
//void load()
//{
//	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
//
//	auto go = std::make_shared<dae::GameObject>();
//	go->AddComponent<RenderComponent>();
//	auto renderComp = go->GetComponent<RenderComponent>();
//	renderComp->SetTexture("background.tga");
//	go->SetLocalPosition(0, 0);
//	scene.Add(go);
//
//	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
//
//	go = std::make_shared<dae::GameObject>();
//	go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
//	go->GetComponent<dae::TextComponent>()->SetLocalPosition(140, 20);
//	scene.Add(go);
//
//	go = std::make_shared<dae::GameObject>();
//	go->AddComponent<dae::TextComponent>("", font);
//	go->GetComponent<dae::TextComponent>()->SetLocalPosition(10, 20);
//	go->AddComponent<dae::FPSComponent>("0", font);
//	scene.Add(go);
//
//
//	auto g0 = std::make_shared<dae::GameObject>();
//	g0->SetLocalPosition(250, 250);
//
//	auto g1 = std::make_shared<dae::GameObject>();
//	g1->SetLocalPosition(150,150);
//	g1->AddComponent<RenderComponent>();
//	g1->AddComponent<RotatorComponent>(2.0f);
//	renderComp = g1->GetComponent<RenderComponent>();
//	renderComp->SetTexture("GalagaSprite01.png");
//
//	auto g2 = std::make_shared<dae::GameObject>();
//	g2->SetLocalPosition(200,200);
//	g2->AddComponent<RenderComponent>();
//	g2->AddComponent<RotatorComponent>(-3.0f);
//	renderComp = g2->GetComponent<RenderComponent>();
//	renderComp->SetTexture("GalagaSprite02.png");
//	
//	g2->SetParent(g1.get());
//	g1->SetParent(g0.get());
//
//	//auto guiObject = std::make_shared<dae::GameObject>();
//	//guiObject->AddComponent<ImGuiComponent>(0,0,150,150);
//
//
//	scene.Add(g0);
//	scene.Add(g1);
//	scene.Add(g2);
//	//scene.Add(guiObject);
//}
//
//int main(int, char*[]) {
//	dae::Minigin engine("../Data/");
//	engine.Run(load);
//    return 0;
//}
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include "ImGuiComponent.h"

#include "Scene.h"
#include "GameObject.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>();
	auto renderComp = go->GetComponent<RenderComponent>();
	renderComp->SetTexture("background.tga");
	go->SetLocalPosition(0, 0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	go->GetComponent<dae::TextComponent>()->SetLocalPosition(140, 20);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>("", font);
	go->GetComponent<dae::TextComponent>()->SetLocalPosition(10, 20);
	go->AddComponent<dae::FPSComponent>("0", font);
	scene.Add(go);


	auto g0 = std::make_shared<dae::GameObject>();
	g0->SetLocalPosition(250, 250);

	auto g1 = std::make_shared<dae::GameObject>();
	g1->SetLocalPosition(150,150);
	g1->AddComponent<RenderComponent>();
	g1->AddComponent<RotatorComponent>(2.0f);
	renderComp = g1->GetComponent<RenderComponent>();
	renderComp->SetTexture("GalagaSprite01.png");

	auto g2 = std::make_shared<dae::GameObject>();
	g2->SetLocalPosition(200,200);
	g2->AddComponent<RenderComponent>();
	g2->AddComponent<RotatorComponent>(-3.0f);
	renderComp = g2->GetComponent<RenderComponent>();
	renderComp->SetTexture("GalagaSprite02.png");
	
	g2->SetParent(g1.get());
	g1->SetParent(g0.get());

	//auto guiObject = std::make_shared<dae::GameObject>();
	//guiObject->AddComponent<ImGuiComponent>(0,0,150,150);


	scene.Add(g0);
	scene.Add(g1);
	scene.Add(g2);
	//scene.Add(guiObject);
}


int main(int, char* []) {
	dae::Minigin engine("../Data/");;
	engine.Run(load);
	return 0;
}
