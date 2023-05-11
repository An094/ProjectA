#include "GameController.h"

using namespace EngineCore;
class GSGameOver : public GameStateBase
{
public:
	GSGameOver() = default;
	~GSGameOver() = default;

	void Init() override;
	void Exit() override {};
	void Update(float deltaTime) override;
	void Draw() override;
	void Pause() override {};

	void HandleKeyEvents(int key, bool bIsPressed) override {};
	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	static void UpdateResult(bool);
private:
	static inline bool isWin = false;
	static inline bool isUpdated = false;
	std::shared_ptr<Texture> m_textures[2];
	std::shared_ptr<Sprite2D> m_background;
	std::shared_ptr<Button> m_retryButton;
	std::shared_ptr<Button> m_quitButton;
};