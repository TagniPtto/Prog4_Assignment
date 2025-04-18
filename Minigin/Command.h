#pragma once



namespace dae {

	struct InputValue {
		float x;
		float y;
	};

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute(const InputValue& value) = 0;
	};


	class GameObject;

	class GameObjectCommand : public Command {
	private:
		GameObject* m_gameObject;
	protected:
		GameObject* GetGameObject() const { return m_gameObject; };
	public:
		virtual void Execute(const InputValue& value) = 0;
		GameObjectCommand();
		virtual ~GameObjectCommand();
	};
	class EditorCommand : public Command {
		~EditorCommand() = default;
		virtual void Undo() = 0;
	};

}

