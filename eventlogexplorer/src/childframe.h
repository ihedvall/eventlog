/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <wx/docmdi.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/treectrl.h>
#include <wx/wx.h>

#include "eventdocument.h"


namespace eventlog {
class ChildFrame : public wxDocMDIChildFrame {
 public:
  ChildFrame(wxDocument *doc,
            wxView *view,
            wxMDIParentFrame *parent,
            wxWindowID id,
            const wxString& title);
  ChildFrame() = default;

  void Update() override;
 protected:
  [[nodiscard]] EventDocument* GetDoc();

 private:
  wxListView* event_view_ = nullptr;
  wxImageList image_list_;

  void RedrawListView();

  void OnListItemActivated(wxListEvent& event);
  wxDECLARE_EVENT_TABLE();
};}




