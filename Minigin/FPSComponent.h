
#pragma once
#include "TextComponent.h"

namespace dae {
    class TextComponent;

    class FPSComponent : public ObjectComponent
    {
    private:
        dae::TextComponent* m_textRenderer;
    public:
        FPSComponent(GameObject& owner, const std::string& text, std::shared_ptr<Font> font);


        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent(const FPSComponent& other) = delete;

        FPSComponent operator=(FPSComponent&& other) = delete;
        FPSComponent operator=(const FPSComponent& other) = delete;

        void Update(float deltaTime) override;
        void Render()const override;
    private:
        float timeCounter;
        int frameCount;
    };
}