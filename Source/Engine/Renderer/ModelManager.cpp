#include "ModelManager.h"

namespace kiko 
{
	ModelManager g_modMan;
	std::shared_ptr<Model> kiko::ModelManager::Get(const std::string& filename)
	{
		if (m_models.find(filename) == m_models.end())
		{
			std::shared_ptr<Model> model = std::make_shared<Model>();
			model->Load(filename);

			m_models[filename] = model;


		}
		return m_models[filename];

	}

}

