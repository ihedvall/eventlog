/*
 * Copyright 2023 Ingemar Hedvall
 * SPDX-License-Identifier: MIT
 */
#include "childframe.h"
#include <util/timestamp.h>
#include <wx/bitmap.h>
#include <wx/sizer.h>
#include <sstream>
#include "eventdocument.h"

#include "windowid.h"

namespace {
#include "img/sub.xpm"
#include "img/tree_list.xpm"
// Bitmap index for the tree control (tree_list.bmp)
constexpr int TREE_ROOT = 0;
constexpr int TREE_ID = 1;
constexpr int TREE_HD = 2;
constexpr int TREE_FH_ROOT = 3;
constexpr int TREE_FH = 4;
constexpr int TREE_DG_ROOT = 5;
constexpr int TREE_DG = 6;
constexpr int TREE_AT_ROOT = 7;
constexpr int TREE_AT = 8;
constexpr int TREE_CH_ROOT = 9;
constexpr int TREE_CH = 10;
constexpr int TREE_EV_ROOT = 11;
constexpr int TREE_EV = 12;
constexpr int TREE_CG = 13;
constexpr int TREE_SI = 14;
constexpr int TREE_CN = 15;
constexpr int TREE_CC = 16;
constexpr int TREE_CA = 17;
constexpr int TREE_DT = 18;
constexpr int TREE_SR = 19;
constexpr int TREE_RD = 20;
constexpr int TREE_SD = 21;
constexpr int TREE_DL = 22;
constexpr int TREE_DZ = 23;
constexpr int TREE_HL = 24;

} // Empty namespace

namespace eventlog {

wxBEGIN_EVENT_TABLE(ChildFrame, wxDocMDIChildFrame)
    EVT_LIST_ITEM_ACTIVATED(kIdPropertyList, ChildFrame::OnListItemActivated)
wxEND_EVENT_TABLE()

ChildFrame::ChildFrame(wxDocument *doc,
                     wxView *view,
                     wxMDIParentFrame *parent,
                     wxWindowID id,
                     const wxString& title)
    : wxDocMDIChildFrame(doc, view, parent, id, title, wxDefaultPosition, wxDefaultSize,
                         wxDEFAULT_FRAME_STYLE, wxASCII_STR(wxFrameNameStr)),
                         image_list_(16,16,false,25) {
#ifdef _WIN32
  wxIcon sub("SUB_ICON", wxBITMAP_TYPE_ICO_RESOURCE);
#else
  wxIcon sub {wxICON(sub)};
#endif
  SetIcon(sub);

  auto* main_panel = new wxPanel(this);
  event_view_ = new wxListView(main_panel, kIdPropertyList, wxDefaultPosition, wxDefaultSize,
                               wxLC_REPORT | wxLC_SINGLE_SEL);
  event_view_->AppendColumn("Property", wxLIST_FORMAT_LEFT, 150);
  event_view_->AppendColumn("Value", wxLIST_FORMAT_LEFT, 200);
  event_view_->AppendColumn("Description", wxLIST_FORMAT_LEFT, 200);

#ifdef _WIN32
  wxBitmap tree_list("TREE_LIST", wxBITMAP_TYPE_BMP_RESOURCE);
#else
  wxBitmap tree_list {wxICON(tree_list)};
#endif

  image_list_.Add(tree_list);
  event_view_->SetImageList(&image_list_, wxIMAGE_LIST_SMALL);

  auto* main_sizer = new wxBoxSizer(wxVERTICAL);
  main_sizer->Add(event_view_, 1 , wxALL | wxGROW,0);
  main_panel->SetSizerAndFit(main_sizer);
}

void ChildFrame::Update() {
  RedrawListView();
}

void ChildFrame::RedrawListView() {
  event_view_->DeleteAllItems();
  /*
  //event_view_->clear();

  auto* doc = GetDoc();
  if (doc == nullptr) {
    return;
  }

  auto id = doc->GetSelectedBlockId();
  const auto* block = doc->GetBlock(id);
  if (block == nullptr) {
    return;
  }

  block->GetBlockProperty(property_list_);

  long line = 0;
  for (const auto& prop : property_list_) {
    switch (prop.Type()) {
      case mdf::detail::BlockItemType::HeaderItem:
      {
        auto index = property_view_->InsertItem(line, wxString::FromUTF8(prop.Label()));
        auto font = property_view_->GetItemFont(index);
        font.MakeItalic();
        property_view_->SetItemFont(index, font);
      }
      break;

      case mdf::detail::BlockItemType::LinkItem:
      {
        auto index = property_view_->InsertItem(line, wxString::FromUTF8(prop.Label()));
        if (prop.Link() > 0) {
          property_view_->SetItem(index, 1, wxString::FromUTF8(prop.Value()));
          property_view_->SetItem(index, 2, wxString::FromUTF8(prop.Description()));
        }
      }
      break;

      case mdf::detail::BlockItemType::BlankItem:
      {
        auto index = property_view_->InsertItem(line, "");
        property_view_->SetItem(index, 1, "");
        property_view_->SetItem(index, 2, "");
      }
        break;

      default:
      {
        auto index = property_view_->InsertItem(line, wxString::FromUTF8(prop.Label()));
        property_view_->SetItem(index, 1, wxString::FromUTF8(prop.Value()));
        property_view_->SetItem(index, 2, wxString::FromUTF8(prop.Description()));
      }
      break;

    }
    ++line;
  }
   */
}

EventDocument *ChildFrame::GetDoc() {
  return wxDynamicCast(GetDocument(),EventDocument );
}
void ChildFrame::OnListItemActivated(wxListEvent &event) {}

}



