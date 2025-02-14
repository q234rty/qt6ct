/*
 * Copyright (c) 2020-2023, Ilya Kotov <forkotov02@ya.ru>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <QSettings>
#include <QStyleFactory>
#include "qt6ctproxystyle.h"

Qt6CTProxyStyle::Qt6CTProxyStyle()
{
    Qt6CT::registerStyleInstance(this);
    Qt6CTProxyStyle::reloadSettings();
}

void Qt6CTProxyStyle::reloadSettings()
{
    QSettings settings(Qt6CT::configFile(), QSettings::IniFormat);
    m_dialogButtonsHaveIcons = settings.value("Interface/dialog_buttons_have_icons", Qt::PartiallyChecked).toInt();
    m_activateItemOnSingleClick = settings.value("Interface/activate_item_on_single_click", Qt::PartiallyChecked).toInt();
    m_underlineShortcut = settings.value("Interface/underline_shortcut", Qt::PartiallyChecked).toInt();

    QString style = settings.value("Appearance/style", "fusion").toString().toLower();
    if(style == "qt6ct-style" || !QStyleFactory::keys().contains(style, Qt::CaseInsensitive))
        style = "fusion";

    if(style != m_style)
    {
        setBaseStyle(QStyleFactory::create(style));
        m_style = style;
    }
}

Qt6CTProxyStyle::~Qt6CTProxyStyle()
{
    Qt6CT::unregisterStyleInstance(this);
}

int Qt6CTProxyStyle::styleHint(QStyle::StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    if(hint == QStyle::SH_DialogButtonBox_ButtonsHaveIcons)
    {
        if(m_dialogButtonsHaveIcons == Qt::Unchecked)
            return 0;
        if(m_dialogButtonsHaveIcons == Qt::Checked)
            return 1;
    }
    else if(hint == QStyle::SH_ItemView_ActivateItemOnSingleClick)
    {
        if(m_activateItemOnSingleClick == Qt::Unchecked)
            return 0;
        if(m_activateItemOnSingleClick == Qt::Checked)
            return 1;
    }
    else if(hint == QStyle::SH_UnderlineShortcut)
    {
        if(m_underlineShortcut == Qt::Unchecked)
            return 0;
        if(m_underlineShortcut == Qt::Checked)
            return 1;
    }
    return QProxyStyle::styleHint(hint, option, widget, returnData);
}
