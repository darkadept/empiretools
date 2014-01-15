#include "searchlistview.h"
#include "ui_searchlistview.h"

class SearchListViewPrivate {
public:

};

SearchListView::SearchListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchListView),
    d(*new SearchListViewPrivate)
{
    ui->setupUi(this);
}

SearchListView::~SearchListView()
{
    delete ui;
    delete &d;
}
