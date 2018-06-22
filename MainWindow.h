#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QModelIndex>
#include "CanAdapter/CanAdapter.h"

namespace Ui {
class MainWindow;
}

class QSortFilterProxyModel;
class CanTreeModel;
class CanAdapter;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onCustomContextMenu(const QPoint &point);

    void on_actionAdd_Group_triggered();
    void tickTimerTimeout();
    void onTransmit(can_message_t cmsg);
    void headerSectionClicked(int index);

    void on_actionSave_Tree_triggered();
    void on_actionLoad_Tree_triggered();
    void on_canAdapterComboBox_currentTextChanged(const QString &arg1);
    void on_actionDeleteTreeNodes_triggered();

    void on_actionAbout_triggered();

    void on_actionSort_Items_Live_triggered(bool checked);

    void on_actionEnableID_triggered(bool checked);
    void on_actionEnableDLC_triggered(bool checked);
    void on_actionEnableCount_triggered(bool checked);
    void on_actionEnablePeriod_triggered(bool checked);
    void on_actionEnableRaw_Data_triggered(bool checked);
    void on_actionEnableDecoded_Data_triggered(bool checked);
    void on_actionEnableFormat_triggered(bool checked);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    CanTreeModel *m_model = 0;
    QSortFilterProxyModel * m_proxyModel = 0;
    const bool useProxyModel = true;

    struct{
        QModelIndex clickedIndex;
    }m_contextMenuContext;

    CanAdapter * m_canAdapter = 0;
    QWidget * m_canAdpterControlWidget = 0;

    QTimer m_tickTimer;

    QList<CanAdapter *>m_canAdapters;

    void changeCanAdpapter(CanAdapter * ca);

    void loadTree(QString &filename);
    bool saveTreeInteractive();
};

#endif // MAINWINDOW_H
