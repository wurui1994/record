#include <QApplication>
#include <QTreeWidget>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTreeWidget *tree = new QTreeWidget;
    QTreeWidgetItem *item;
    QTreeWidgetItem *child;
    tree->setDragDropMode(QAbstractItemView::DragDrop);
    tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tree->setDefaultDropAction(Qt::MoveAction);
    tree->setDragEnabled(true);
    tree->setAcceptDrops(true);
    tree->setDropIndicatorShown(true);
    //disable dropping of leaves as top level items
//    tree->invisibleRootItem()->setFlags( Qt::ItemIsSelectable |
//                    Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
    for (int i = 0; i < 2; i++) {
        // create top level item
        item = new QTreeWidgetItem();
        item->setText(0, "parent");
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
                      | Qt::ItemIsDropEnabled|Qt::ItemIsDragEnabled | Qt::ItemIsEnabled );
        // add 3 child items
        for (int j = 0; j < 3; j++) {
            child = new QTreeWidgetItem();
            child->setText(0, QString("child%1%2").arg(i).arg(j));
            child->setFlags(
                          Qt::ItemIsSelectable |Qt::ItemIsDragEnabled|Qt::ItemIsDragEnabled | Qt::ItemIsEnabled );
            item->addChild(child);
        }
        // add item to tree
        tree->addTopLevelItem(item);
    }
    tree->show();
    return app.exec();
}