#include "conf.h"

#include <spdlog/spdlog.h>

using namespace libconfig;

ConfigFile::ConfigFile(std::string path) {
    try {
        m_config.readFile("settings.cfg");
    } catch (const FileIOException &fioex) {
        spdlog::error("I/O error while reading file.");
    } catch (const ParseException &pex) {
        spdlog::error("Parse error at {0}: {1} - {2}", pex.getFile(),
                      pex.getLine(), pex.getError());
    }
}

ConfigFile::~ConfigFile() {}

Setting &ConfigFile::root() { return m_config.getRoot(); }
