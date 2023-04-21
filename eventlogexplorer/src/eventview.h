/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <wx/docview.h>

#include "eventdocument.h"

namespace eventlog {
 class EventView : public wxView  {
  public:
   EventView() = default;
   EventDocument* GetDocument() const;

   bool OnCreate(wxDocument* doc, long flags) override;
   bool OnClose(bool del) override;

   void OnDraw(wxDC *dc) override;
   void OnUpdate(wxView *sender, wxObject *hint = nullptr) override;

  private:

   wxDECLARE_DYNAMIC_CLASS(EventView);

 };
}





