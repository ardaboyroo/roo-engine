#include "Layer.hpp"

namespace roo
{
    Layer::Layer(const std::string& name)
        : m_LayerName(name)
    {
    }

    void Layer::AddGameObject(std::shared_ptr<GameObject> object)
    {
        m_Children.push_back(object);
    }

    std::vector<std::shared_ptr<GameObject>>& Layer::GetChildren()
    {
        return m_Children;
    }


}
