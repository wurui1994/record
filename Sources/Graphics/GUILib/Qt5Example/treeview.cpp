#include <QApplication>
#include <QTreeView>
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QDropEvent>
#include <QDebug>

class TreeView:public QTreeView
{
public:
    void dropEvent(QDropEvent*e);
};

void TreeView::dropEvent(QDropEvent *e)
{
    qDebug()<<"dropEvent";
    QTreeView::dropEvent(e);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TreeView *tree = new TreeView;
    //tree->setDragDropMode(QAbstractItemView::DragDrop);
    //tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tree->setDefaultDropAction(Qt::MoveAction);
    tree->setDragEnabled(true);
    tree->setAcceptDrops(true);
    tree->setDropIndicatorShown(true);
    Qt::ItemFlags flags = Qt::ItemIsSelectable |Qt::ItemIsDragEnabled|Qt::ItemIsDragEnabled | Qt::ItemIsEnabled|Qt::ItemIsEditable;//|Qt::ItemNeverHasChildren;
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item = new QStandardItem(QString("TEST 1"));
    item->setFlags(flags);
    model->setItem(0, 0, item);
    QStandardItem *item2 = new QStandardItem(QString("TEST 2"));
    item2->setFlags(flags);
    model->setItem(1, 0, item2);
    tree->setModel(model);


    tree->show();
    return app.exec();
}
