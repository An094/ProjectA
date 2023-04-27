#include "Objects/Sprite2D.h"
#include "Manager/ResourceManager.h"

class Cloud
{
public:
	Cloud(const std::string&);
	Cloud(const std::string&, int, int, int, int);
	Cloud(const std::string&, glm::vec2, int, int);
	~Cloud() = default;

	void LoadResource();

	void SetPosition(float, float);
	void SetPosition(glm::vec2);
	void Render();
	void Update(float);

private:
	std::string m_textureFile;
	std::shared_ptr<EngineCore::Sprite2D> m_sprite;
	glm::vec2 m_position;
	int m_width, m_height;
};