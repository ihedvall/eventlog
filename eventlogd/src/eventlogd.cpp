/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
*/


#include <atomic>
#include <chrono>
#include <csignal>
#include <filesystem>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <iostream>
#include <boost/program_options.hpp>

#include <util/ixmlfile.h>
#include <util/logconfig.h>
#include <util/logstream.h>
#include <util/utilfactory.h>

#include "eventlogserver.h"

using namespace util::log;
using namespace util::xml;
using namespace std::chrono_literals;
using namespace boost::program_options;
using namespace std::filesystem;
using namespace eventlog;


namespace {
std::atomic<bool> kStopMain = false;

void StopMainHandler(int signal) {
  kStopMain = true;
  LOG_TRACE() << "Stopping Event Log Server. Signal: " << signal;
  for (size_t count = 0; count < 100 && kStopMain; ++count) {
    std::this_thread::sleep_for(100ms);
  }
}

}  // namespace


int main(int nof_arg, char* arg_list[]) {
  signal(SIGTERM, StopMainHandler);
  signal(SIGABRT, StopMainHandler);
#if (_MSC_VER)
  signal(SIGABRT_COMPAT, StopMainHandler);
  signal(SIGBREAK, StopMainHandler);
#endif

  // Set log file name to the service name
  auto& log_config = LogConfig::Instance();
  log_config.Type(LogType::LogToFile);
  log_config.SubDir("eventlog/log"); // Hint of relative path
  log_config.BaseName("eventlogd"); // Log file name without extension (stemm)
  log_config.CreateDefaultLogger(); // Create logger with name 'Default"


  // Log to console if in debug mode
#ifdef _DEBUG
  std::vector<std::string> empty_list;
  auto log_console = util::UtilFactory::CreateLogger(LogType::LogToConsole,
                      empty_list);
  log_config.AddLogger("Console", std::move(log_console));
#endif
  LOG_TRACE() << "Log File created. Path: " << log_config.GetLogFile();

  EventLogServer server;

  // Scan through input arguments
  try {
    std::vector<std::string> config_list;
    options_description desc("Available Options");
    desc.add_options()
        ("help,H", "Shows available input arguments")
        ("config,C", value(&config_list), "Config file (XML)");

    positional_options_description pos;
    pos.add("config", -1);

    command_line_parser parser(nof_arg,arg_list);
    parser.options(desc);
    parser.positional(pos);
    const auto opt = parser.run();
    variables_map vm;
    store(opt, vm);
    notify(vm);
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      kStopMain = false;
      return EXIT_SUCCESS;
    }
    if (!config_list.empty()) {
      server.ConfigFile(config_list.back());
    }
  } catch (const std::exception& err ) {
    LOG_ERROR() << "Fail to parse the input arguments. Error: " << err.what();
  }

  try {
    path app_root(ProgramDataPath());
    path data_dir = app_root.append("eventlog");
    server.DataPath(data_dir.string());
    if (!exists(data_dir)) {
      create_directories(data_dir);
    }
  } catch (const std::exception& err) {
    LOG_ERROR() << "Data Directory error: " << err.what();
  }
  LOG_TRACE() << "Program Data Path: " << server.DataPath();

  if (server.ConfigFile().empty()) {
    // If eventlog.xml file exist in data directory, use it otherwise create
    // a default server.
    try {
      path data_dir(server.DataPath());
      path config_file = data_dir.append("eventlog.xml");
      if (exists(config_file)) {
        server.ConfigFile(config_file.string());
      } else {
        server.CreateDefaultConfigFile(config_file.string());
      }

    } catch (const std::exception& err) {
      LOG_ERROR() << "Create default config file failed. Error: "
        << err.what();
    }
  }

  if (server.ConfigFile().empty()) {
    LOG_ERROR() << "Failed to find any config file (empty)";
    return EXIT_FAILURE;
  }
  LOG_TRACE() << "Config File: " << server.ConfigFile();

  auto xml_file = CreateXmlFile("Expat");
  if (!xml_file) {
    LOG_ERROR() << "Failed to create Expat XML file";
    return EXIT_FAILURE;
  }


  xml_file->FileName(server.ConfigFile());
  const auto parse = xml_file->ParseFile();
  auto* root = xml_file->RootNode();
  if (!parse  || root == nullptr) {
    LOG_ERROR() << "Failed to parse the config file. File: "
                << server.ConfigFile();
    return EXIT_FAILURE;
  }

  server.ReadXml(*root);
  server.Init();
  while (!kStopMain) {
    server.Tick();
    std::this_thread::sleep_for(10ms);
  }
  server.Exit();
  kStopMain = false;
  server.Clear();

  LOG_TRACE() << "Stopped event log daemon";

  log_config.DeleteLogChain();

  return EXIT_SUCCESS;
}
