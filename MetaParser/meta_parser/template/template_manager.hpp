#pragma once
#include <string>
#include <unordered_map>
#include "../common/schema_module.h"
#include "../common/parser_utils.h"

class TemplateManager
{
public:
    static TemplateManager* GetInstance()
    {
        static TemplateManager* m_pInstance;
        if (nullptr == m_pInstance)
            m_pInstance = new TemplateManager();
        return m_pInstance;
    }
    inline void LoadTemplates(std::string path, std::string template_name) {
        m_template_pool.insert_or_assign(template_name, Utils::loadFile("../template/" + template_name + ".mustache")); // path + "/../template/"
    }

    inline std::string RenderByTemplate(std::string template_name, Mustache::data& template_data) {
        if (m_template_pool.end() == m_template_pool.find(template_name))
        {
            return "";
        }
        Mustache::mustache tmpl(m_template_pool[template_name]);
        return tmpl.render(template_data);
    }

    TemplateManager(const TemplateManager&) = delete;
    TemplateManager& operator=(const TemplateManager&) = delete;

private:
    TemplateManager() {}
    
    std::unordered_map<std::string, std::string> m_template_pool;
};
