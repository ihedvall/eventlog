/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#include "eventlogserver.h"
#include <util/ixmlfile.h>
#include <util/logstream.h>

using namespace util::xml;
using namespace util::log;

namespace eventlog {

void EventLogServer::CreateDefaultConfigFile(const std::string& file) {
  if (config_file_.empty()) {
    config_file_ = file;
  }

  auto xml_file = CreateXmlFile("FileWriter");
  if (!xml_file) {
    LOG_ERROR() << "Failed to create XML writer file";
    return;
  }

  try {
    auto& root = xml_file->RootName("EventLogServer");
    auto& app =  root.AddUniqueNode("Application");
    app.SetProperty<std::string>("Name", "Event Log Server");
    app.SetProperty<std::string>("Description",
                     "Default event log server based upon SQLite database");

  } catch (const std::exception& err) {
    LOG_ERROR() << "Failed to create config file. Error: " << err.what();
  }
}

}  // namespace eventlog