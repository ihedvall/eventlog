/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <memory>
#include <wx/docview.h>
#include <wx/wx.h>
#include <util/isyslogserver.h>

namespace eventlog {

class EventDocument : public wxDocument {
 public:
  EventDocument() = default;
  ~EventDocument() override = default;
  bool OnNewDocument() override;
  bool OnOpenDocument(const wxString &filename) override;

 private:
  std::unique_ptr<util::syslog::ISyslogServer> client_;
  wxDECLARE_DYNAMIC_CLASS(EventDocument);
  wxDECLARE_EVENT_TABLE();
};



}



