/*
* Copyright 2023 Ingemar Hedvall
* SPDX-License-Identifier: MIT
 */

#pragma once
#include <string>
#include <genericworkflowserver.h>
namespace eventlog {

class EventLogServer : public workflow::GenericWorkflowServer {
 public:
  void ConfigFile(const std::string& file) {
    config_file_ = file;
  }
  [[nodiscard]] const std::string& ConfigFile() const {
    return config_file_;
  }

  void DataPath(const std::string& path) {
    data_path_ = path;
  }
  [[nodiscard]] const std::string& DataPath() const {
    return data_path_;
  }

  void CreateDefaultConfigFile(const std::string& file);
 private:
  std::string config_file_; ///< Full path to configuration file
  std::string data_path_; ///< Application data path
};

}  // namespace eventlog
