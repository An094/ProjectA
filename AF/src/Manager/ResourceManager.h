#pragma once
#include<iostream>
#include <map>
#include<memory>
#include "Objects/Texture.h"
#include "Objects/shaderClass.h"
#include "Objects/Model.h"
#include "soloud.h"
#include "soloud_wav.h"
#include <vector>

namespace EngineCore
{

	enum AUDIO_TYPE
	{
		MUSIC = 0,
		SOUND
	};

	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();
		static std::shared_ptr<ResourceManager> GetInstance();
		void Init();
		void AddShader(const std::string& name);
		void AddTexture(const std::string& name);
		void AddModel(const std::string& name);

		//Sound
		void AddSound(AUDIO_TYPE type, const std::string& name);
		void PlaySound(AUDIO_TYPE type, const std::string& name, bool loop = false);
		void PauseSound(const std::string& name);

		std::shared_ptr<Shader> GetShader(const std::string& name);
		std::shared_ptr<Texture> GetTexture(const std::string& name);
		std::shared_ptr<Model> GetModel(const std::string& name);

		void SetVolume(AUDIO_TYPE type, float volume);
	private:
		std::string m_DataPath;
		std::string m_ShaderPath;
		std::string m_TexturePath;
		std::string m_ModelPath;
		std::string m_SoundsPath;//Add soundsPath

		std::map<std::string, std::shared_ptr<Shader>> m_MapShader;
		std::map<std::string, std::shared_ptr<Texture>> m_MapTexture;
		std::map<std::string, std::shared_ptr<Model>> m_MapModel;
		std::map<std::string, std::shared_ptr<SoLoud::Wav>> m_MapWave;//Add mapSound;

		std::vector<SoLoud::handle> m_ListHandleMusic;
		std::vector<SoLoud::handle> m_ListHandleSound;

		SoLoud::Soloud m_Soloud;

		static std::shared_ptr<ResourceManager> s_Instance;
	};

}
