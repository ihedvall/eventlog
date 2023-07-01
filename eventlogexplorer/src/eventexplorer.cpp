/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <filesystem>
#define BOOST_LOCALE_HIDE_AUTO_PTR
#include <wx/config.h>
#include <wx/docview.h>
#include <wx/utils.h>
#include <wx/wx.h>

#include <boost/filesystem.hpp>
#include <boost/locale.hpp>
#include <boost/process.hpp>

#include "eventdocument.h"
#include "eventexplorer.h"
#include "eventview.h"
#include "mainframe.h"
#include <util/logstream.h>
#include <util/logconfig.h>

#include "windowid.h"

using namespace util::log;

wxIMPLEMENT_APP(eventlog::EventExplorer);

namespace eventlog {

wxBEGIN_EVENT_TABLE(EventExplorer, wxApp)
  EVT_UPDATE_UI(kIdOpenLogFile,EventExplorer::OnUpdateOpenLogFile)
  EVT_MENU(kIdOpenLogFile, EventExplorer::OnOpenLogFile)
wxEND_EVENT_TABLE()

bool EventExplorer::OnInit() {
  if (!wxApp::OnInit()) {
    return false;
  }

  // Setup correct localization when formatting date and times
  boost::locale::generator gen;
  std::locale::global(gen(""));

    // Setup system basic configuration
  SetVendorDisplayName("Event Log");
  SetVendorName("EventLog");
  SetAppDisplayName("Event Log Explorer");
  SetAppName("EventLogExplorer");


  // Set up the log file.
  // The log file will be in %TEMP%/report_server/mdf_viewer.log
  auto& log_config = LogConfig::Instance();
  log_config.Type(LogType::LogToFile);
  log_config.SubDir("eventlog/log");
  log_config.BaseName("eventlogexplorer");
  log_config.CreateDefaultLogger();
  LOG_TRACE() << "Log File created. Path: " << log_config.GetLogFile();

  notepad_ = util::log::FindNotepad();

  auto* app_config = wxConfig::Get();
  wxPoint start_pos;
  app_config->Read("/MainWin/X",&start_pos.x, wxDefaultPosition.x);
  app_config->Read("/MainWin/Y",&start_pos.y, wxDefaultPosition.x);
  wxSize start_size;
  app_config->Read("/MainWin/XWidth",&start_size.x, 1200);
  app_config->Read("/MainWin/YWidth",&start_size.y, 800);
  bool maximized = false;
  app_config->Read("/MainWin/Max",&maximized, maximized);

  auto* doc_manager = new wxDocManager;
  new wxDocTemplate(doc_manager, "Workflow File","*.xml","",
                                         "xml","EventLog","Event Log Explorer",
                                         wxCLASSINFO(EventDocument), wxCLASSINFO(EventView));
  auto* frame = new MainFrame(GetAppDisplayName(), start_pos, start_size, maximized);

  frame->Show(true);

  return true;
}

int EventExplorer::OnExit() {
  LOG_INFO() << "Closing application";
  auto* app_config = wxConfig::Get();
  auto* doc_manager = wxDocManager::GetDocumentManager();
  doc_manager->FileHistorySave(*app_config);
  delete doc_manager;
  LOG_INFO() << "Saved file history.";

  auto& log_config = LogConfig::Instance();
  log_config.DeleteLogChain();
  return wxApp::OnExit();
}

void EventExplorer::OnOpenLogFile(wxCommandEvent& event) {
  auto& log_config = LogConfig::Instance();
  std::string logfile = log_config.GetLogFile();
  OpenFile(logfile);
}

void EventExplorer::OnUpdateOpenLogFile(wxUpdateUIEvent &event) {
  if (notepad_.empty()) {
    event.Enable(false);
    return;
  }

  auto& log_config = LogConfig::Instance();
  std::string logfile = log_config.GetLogFile();
  try {
    std::filesystem::path p(logfile);
    const bool exist = std::filesystem::exists(p);
    event.Enable(exist);
  } catch (const std::exception&) {
    event.Enable(false);
  }
}

void EventExplorer::OpenFile(const std::string& filename) const {
  if (!notepad_.empty()) {
    boost::process::spawn(notepad_, filename);
  }
}

}


