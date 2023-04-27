#include "Objects/Sprite2D.h"
#include "Manager/ResourceManager.h"

class Platformer
{
public:
	Platformer(const std::string&);
	Platformer(const std::string&, int, int, int, int);
	Platformer(const std::string&, glm::vec2, int, int);
	~Platformer() = default;

	void LoadResource();
	bool IsCollision();

	void SetPosition(int, int);
	void SetPosition(glm::vec2);
	void Render();

private:
	std::string m_textureFile;
	std::shared_ptr<EngineCore::Sprite2D> m_sprite;
	glm::vec2 m_position;
	int m_width, m_height;
};