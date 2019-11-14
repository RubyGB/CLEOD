#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QRect>
#include <QPainter>
#include <QTextBlock>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QPlainTextEdit>

class TextEditor: public QPlainTextEdit{
    Q_OBJECT

public:
    TextEditor(QWidget *parent = 0);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
};

#endif // TEXTEDITOR_H
