#include <string>

#include <libconfig.h++>

using namespace libconfig;

class ConfigFile {
    std::string m_storage_path;
    Config m_config;

   public:
    ConfigFile(std::string);
    virtual ~ConfigFile();
    Setting& root();
};
