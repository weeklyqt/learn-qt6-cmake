#include "ctheme.h"

CTheme::CTheme(QObject *parent)
    : QObject{parent}
{
    m_darkTheme = false;
    m_windowColor = "#ffffff";
    m_buttonBackgroundColor = "#fbfbfd";
    m_buttonTextColor = "#000000";
}

void CTheme::setDarkTheme(bool isDark)
{
    qDebug() << Q_FUNC_INFO;
    if (isDark == m_darkTheme)
        return ;

    m_darkTheme = isDark;

    if (m_darkTheme) {
        m_windowColor = "#2e2f30";
        m_buttonBackgroundColor = "#1f1f1f";
        m_buttonTextColor = "#b2b2b2";
    } else {
        m_windowColor = "#ffffff";
        m_buttonBackgroundColor = "#fbfbfd";
        m_buttonTextColor = "#000000";
    }

    emit darkThemeChanged();
    emit windowColorChanged();
    emit buttonBackgroundColorChanged();
    emit buttonTextColorChanged();
}

bool CTheme::darkTheme()
{
    return m_darkTheme;
}
