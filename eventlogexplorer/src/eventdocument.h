/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <wx/docview.h>
#include <wx/wx.h>

namespace eventlog {

class EventDocument : public wxDocument {
 public:
  EventDocument() = default;
  ~EventDocument() override = default;

  bool OnOpenDocument(const wxString &filename) override;

 private:

  wxDECLARE_DYNAMIC_CLASS(EventDocument);
  wxDECLARE_EVENT_TABLE();
};



}



