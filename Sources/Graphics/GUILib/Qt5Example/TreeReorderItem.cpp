#include <QApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDropEvent>

class TreeView : public QTreeWidget
{
public:
	TreeView()
	{
		resize(200, 300);

		setSelectionMode(QAbstractItemView::SingleSelection);
		setDragEnabled(true);
		viewport()->setAcceptDrops(true);
		setDropIndicatorShown(true);
		setDragDropMode(QAbstractItemView::InternalMove);

		QTreeWidgetItem* parentItem = new QTreeWidgetItem(this);
		parentItem->setText(0, "Test");
		parentItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled);

		for (int i = 0; i < 10; ++i)
		{
			QTreeWidgetItem* pItem = new QTreeWidgetItem(parentItem);
			pItem->setText(0, QString("Number %1").arg(i));
			pItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
			pItem->addChild(pItem);
		}
	}

private:
	virtual void  dropEvent(QDropEvent * event)
	{
		QModelIndex droppedIndex = indexAt(event->pos());

		if (!droppedIndex.isValid())
			return;

		QTreeWidget::dropEvent(event);
	}
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	TreeView widget;
	widget.show();

	return a.exec();
}