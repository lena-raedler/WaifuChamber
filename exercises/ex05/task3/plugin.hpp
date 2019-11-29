#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <memory>

/// Interface for plugins.
class Plugin {
  public:
	virtual void run() = 0;
	virtual ~Plugin(){};
};

/// Symbol of the plugin construtor function.
const auto PLUGIN_CONSTRUCTOR_SYMBOL = "create_plugin";

/// Type of the plugin constructor function.
using PLUGIN_CONSTRUCTOR = std::unique_ptr<Plugin> (*)();

#endif
