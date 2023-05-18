#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtDataVisualization/q3dscatter.h"
#include "scatterdatamodifier.h"
#include "QTranslator"

QT_BEGIN_NAMESPACE
class QAbstractButton;
class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
QT_END_NAMESPACE

using namespace QtDataVisualization;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open_File(QString fileName);

private slots:
    void on_action_ffnen_triggered();

    void on_action_Beenden_triggered();

    void setup_scatter();

    void change_language(QString language);

    void set_style_actions_to_false();

    void on_action_Qt_triggered();

    void on_action_Primary_Colors_triggered();

    void on_action_Digia_triggered();

    void on_action_Stone_Moss_triggered();

    void on_action_Army_Blue_triggered();

    void on_action_Retro_triggered();

    void on_action_Ebony_triggered();

    void on_action_Isabelle_triggered();

    void on_action_ber_triggered();

    void on_action_Hintergrund_darstellen_triggered();

    void on_action_Gitter_darstellen_triggered();

    void on_action_Englisch_triggered();

    void on_action_Deutsch_triggered();

    void on_action_Franz_sisch_triggered();



private:
    Ui::MainWindow *ui;
    QTranslator m_translator; // contains the translations for this application

    Q3DScatter *graph;
    ScatterDataModifier *modifier;

    QStringList findQmFiles();
    QString languageName(const QString &qmFile);
    static bool languageMatch(const QString& lang, const QString& qmFile);

    void switchTranslator(QTranslator& translator, const QString& filename);

protected:

    void dragEnterEvent(QDragEnterEvent *e);

    void dropEvent(QDropEvent *e);

    void changeEvent(QEvent *);
};

#endif // MAINWINDOW_H
