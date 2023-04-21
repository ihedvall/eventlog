/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include <wx/docmdi.h>

#include "childframe.h"
#include "eventexplorer.h"
#include "eventview.h"

namespace eventlog {

wxIMPLEMENT_DYNAMIC_CLASS(EventView,wxView)

EventDocument *EventView::GetDocument() const {
  return wxDynamicCast(wxView::GetDocument(),EventDocument );
}

void EventView::OnDraw(wxDC*) {
}

bool EventView::OnCreate(wxDocument *doc, long flags) {
  if (!wxView::OnCreate( doc,flags)) {
    return false;
  }

  auto & app = wxGetApp();
  auto* parent = wxDynamicCast(app.GetTopWindow(),wxMDIParentFrame);
  wxFrame* sub_frame = new ChildFrame(doc, this, parent,wxID_ANY,"Event Log File");
  sub_frame->Show();
  return true;
}

bool EventView::OnClose(bool del) {
  return wxView::OnClose(del);
}
void EventView::OnUpdate(wxView *sender, wxObject *hint) {
  wxView::OnUpdate(sender, hint);
  auto* frame = GetFrame();
  if (frame != nullptr) {
    frame->Update();
  }
}

}