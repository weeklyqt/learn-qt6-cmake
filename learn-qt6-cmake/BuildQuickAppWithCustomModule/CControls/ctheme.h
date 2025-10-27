#ifndef CTHEME_H
#define CTHEME_H

#include <QObject>
#include <QQmlEngine>
#include <QColor>

class CTheme : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(bool darkTheme READ darkTheme WRITE setDarkTheme NOTIFY darkThemeChanged FINAL)
    Q_PROPERTY(QColor windowColor MEMBER m_windowColor NOTIFY windowColorChanged FINAL)
    Q_PROPERTY(QColor buttonBackgroundColor MEMBER m_buttonBackgroundColor NOTIFY buttonBackgroundColorChanged FINAL)
    Q_PROPERTY(QColor buttonTextColor MEMBER m_buttonTextColor NOTIFY buttonTextColorChanged FINAL)
public:
    explicit CTheme(QObject *parent = nullptr);

    void setDarkTheme(bool isDark);
    bool darkTheme();
signals:
    void darkThemeChanged();
    void windowColorChanged();
    void buttonBackgroundColorChanged();
    void buttonTextColorChanged();
private:
    bool m_darkTheme;
    QColor m_windowColor;
    QColor m_buttonBackgroundColor;
    QColor m_buttonTextColor;
};

#endif // CTHEME_H
