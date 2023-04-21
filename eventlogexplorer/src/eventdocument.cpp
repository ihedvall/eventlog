/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <sstream>

#include <filesystem>

#include <wx/msgdlg.h>
#include "eventdocument.h"
#include "eventexplorer.h"
#include "util/logstream.h"
#include "windowid.h"

using namespace util::log;



namespace eventlog {
wxIMPLEMENT_DYNAMIC_CLASS(EventDocument, wxDocument) // NOLINT

wxBEGIN_EVENT_TABLE(EventDocument, wxDocument) // NOLINT
wxEND_EVENT_TABLE()

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