#include "ResourceManager.h"
#include "Common.h"

namespace EngineCore
{

	std::shared_ptr<ResourceManager> ResourceManager::s_Instance = nullptr;

	std::shared_ptr<ResourceManager> ResourceManager::GetInstance()
	{
		if (s_Instance == nullptr)
			s_Instance = std::make_shared<ResourceManager>();
		return s_Instance;
	}

	ResourceManager::ResourceManager()
	{
		m_DataPath = "../Data/";
		m_ShaderPath = m_DataPath + "Shaders/";
		m_TexturePath = m_DataPath + "Textures/";
		m_ModelPath = m_DataPath + "Models/";
		m_SoundsPath = m_DataPath + "Sounds/";
	}

	ResourceManager::~ResourceManager()
	{

	}
	//Load data from files named in Data.inl
	void ResourceManager::Init()
	{
		std::string initFileName = m_DataPath + "Data.inl";
		std::string buffer = Common::get_file_contents(initFileName.c_str());
		std::stringstream ss(buffer);
		std::string strtmp;
		int numModel, numShader;
		std::getline(ss, strtmp, '\n');
		sscanf_s(strtmp.c_str(), "#Models %d", &numModel);
		for (int i = 0; i < numModel; i++)
		{
			std::getline(ss, strtmp, '\n');
			strtmp = strtmp.substr(0, strtmp.size());
			// Remove newline characters from string in C++
			strtmp.erase(std::remove_if(strtmp.begin(),
				strtmp.end(),
				[](auto ch)
				{
					return (ch == '\n' ||
						ch == '\r');
				}),
				strtmp.end());
			AddModel(strtmp);
		}
		std::getline(ss, strtmp, '\n');
		sscanf_s(strtmp.c_str(), "#Shaders %d", &numShader);
		for (int i = 0; i < numShader; i++)
		{
			std::getline(ss, strtmp, '\n');
			strtmp = strtmp.substr(0, strtmp.size());
			// Remove newline characters from string in C++
			strtmp.erase(std::remove_if(strtmp.begin(),
				strtmp.end(),
				[](auto ch)
				{
					return (ch == '\n' ||
						ch == '\r');
				}),
				strtmp.end());
			AddShader(strtmp);
		}
		m_Soloud = SoLoud::Soloud();
		m_Soloud.init();
	}

	void ResourceManager::AddShader(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Shader>>::iterator it = m_MapShader.find(name);
		if (it != m_MapShader.end())
		{
			return;
		}

		std::shared_ptr<Shader>  shader;
		std::string vsPath = m_ShaderPath + name + ".vs";
		std::string fsPath = m_ShaderPath + name + ".fs";
		shader = std::make_shared<Shader>(vsPath.c_str(), fsPath.c_str());

		m_MapShader[name] = shader;

	}

	void ResourceManager::AddModel(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Model>>::iterator it = m_MapModel.find(name);
		if (it != m_MapModel.end())
		{
			return;
		}
		std::shared_ptr<Model>  model;
		std::string path = m_ModelPath + name + ".txt";
		model = std::make_shared<Model>(path.c_str());

		m_MapModel[name] = model;

	}

	void ResourceManager::AddTexture(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Texture>>::iterator it = m_MapTexture.find(name);
		if (it != m_MapTexture.end())
		{
			return;
		}
		std::shared_ptr<Texture> texture;
		std::string path = m_TexturePath + name;
		texture = std::make_shared<Texture>(path.c_str());

		m_MapTexture[name] = texture;
	}

	std::shared_ptr<Model> ResourceManager::GetModel(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Model>>::iterator  it = m_MapModel.find(name);
		if (it != m_MapModel.end())
		{
			return it->second;
		}

		std::shared_ptr<Model>  model;
		std::string path = m_ModelPath + name + ".txt";
		model = std::make_shared<Model>(path.c_str());
		return model;
	}

	std::shared_ptr<Shader> ResourceManager::GetShader(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Shader>>::iterator  it = m_MapShader.find(name);
		if (it != m_MapShader.end())
		{
			return it->second;
		}

		std::shared_ptr<Shader>  shader;
		std::string vs = m_ShaderPath + name + ".vs";
		std::string fs = m_ShaderPath + name + ".fs";
		shader = std::make_shared<Shader>(vs.c_str(), fs.c_str());
		return shader;
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& name)
	{
		std::map<std::string, std::shared_ptr<Texture>>::iterator it = m_MapTexture.find(name);
		if (it != m_MapTexture.end())
		{
			return it->second;
		}

		std::shared_ptr<Texture> texture;
		std::string path = m_TexturePath + name;
		texture = std::make_shared<Texture>(path.c_str());

		return texture;
	}

	void ResourceManager::PlaySound(AUDIO_TYPE type, const std::string& name, bool loop)
	{
		std::shared_ptr<SoLoud::Wav> wave;
		auto it = m_MapWave.find(name);
		if (it != m_MapWave.end())
		{
			wave = it->second;
		}
		else
		{
			std::string wav = m_SoundsPath + name;
			wave = std::make_shared<SoLoud::Wav>();
			wave->load(wav.c_str());
			m_MapWave.insert(std::pair<std::string, std::shared_ptr<SoLoud::Wav>>(name, wave));
		}
		auto h = m_Soloud.play(*wave);
		if (type == AUDIO_TYPE::SOUND)
		{
			m_ListHandleSound.push_back(h);
		}
		else
		{
			m_ListHandleMusic.push_back(h);
		}
		m_Soloud.setLooping(h, loop);
	}

	void ResourceManager::PauseSound(const std::string& name)
	{
		std::shared_ptr<SoLoud::Wav> wave;
		auto it = m_MapWave.find(name);
		if (it != m_MapWave.end())
		{
			wave = it->second;
		}
		m_Soloud.stopAudioSource(*wave);
	}

	void ResourceManager::SetVolume(AUDIO_TYPE type, float volume)
	{
		if (type == AUDIO_TYPE::MUSIC)
		{
			for (auto it : m_ListHandleMusic)
			{
				m_Soloud.setVolume(it, volume);
			}
		}
		else
		{
			for (auto it : m_ListHandleSound)
			{
				m_Soloud.setVolume(it, volume);
			}
		}
	}

}
