/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <sstream>

#include <filesystem>

#include <wx/msgdlg.h>
#include "eventdocument.h"
#include "eventexplorer.h"
#include <util/logstream.h>
#include <util/utilfactory.h>
#include "windowid.h"


using namespace util::log;
using namespace util::syslog;


namespace eventlog {
wxIMPLEMENT_DYNAMIC_CLASS(EventDocument, wxDocument) // NOLINT

wxBEGIN_EVENT_TABLE(EventDocument, wxDocument) // NOLINT
wxEND_EVENT_TABLE()

bool EventDocument::OnNewDocument() {
  auto temp = util::UtilFactory::CreateSyslogServer(
      SyslogServerType::TcpSubscriber);
  if (!temp) {
    return false;
  }

  return true;
}

bool EventDocument::OnOpenDocument(const wxString &filename) {

  wxBusyCursor wait;
  const auto parse = true;
  if (!parse) {
    wxMessageBox(wxString("Failed to parse the file.\nMore information in the log file."),
                 wxString("Error Parsing File"),
                 wxOK | wxCENTRE | wxICON_ERROR);
  }
  return parse && wxDocument::OnOpenDocument(filename);
}

} // namespace eventlog