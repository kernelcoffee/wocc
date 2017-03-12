/**
 * Copyright (C) 2011-2014 Alexandre Moore <alexandre@kernelcoffee.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "logger.h"
#include <QDir>
#include <iostream>
#include <QtCore/QStandardPaths>
#include <QDateTime>

const static QString    DEFAULT_LOG_DIR = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/Kernelcoffee/ErgoMusic/logs";	///< Log directory
const static QString    DEFAULT_LOG_FILE = "logFile";	///< Log file name
const static QString    DEFAULT_LOG_EXT = "log";
const static bool       WRITE_IN_LOGFILE = true;

static const QString	logLevel_str[] = {
    "Debug",
    "Warning",
    "Critical",
    "Fatal",
    "Info",
    "System"
};

Logger::Logger(QObject *parent) :
    QObject(parent)
  , _logFile(nullptr)
{}

Logger::~Logger()
{
    if (_logFile) {
        if (_logFile->isOpen())
            _logFile->close();
         delete _logFile;
    }
}

void Logger::log(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Logger* logger = Logger::instance();
    QString message = Logger::instance()->_getLogPrefix()
            + logLevel_str[type]
            + ",\t" + context.file
            + ",\t" + QString::number(context.line)
            + ",\t" + context.function
            + ",\t" + msg
            ;

    if (logger->outputToStd() && logger->fullDebugOutput()) {
        logger->_outputToStd(type, message);
    } else if (logger->outputToStd()) {
        logger->_outputToStd(type, msg);
    }

    logger->_write(message);
    if (type == QtFatalMsg) {
        abort();
    }
}

void Logger::notice(const QString &msg)
{
    QString message = Logger::instance()->_getLogPrefix()
            + msg
            + "\n";

    std::cout << message.toStdString();
    Logger::instance()->_write(message);
}

void Logger::setOutputToStd(bool outputToStd)
{
    m_outputToStd = outputToStd;
}

void Logger::setFullDebugOutput(bool fullDebugOutput)
{
    m_fullDebugOutput = fullDebugOutput;
}

bool Logger::outputToStd()
{
    return m_outputToStd;
}

bool Logger::fullDebugOutput()
{
    return m_fullDebugOutput;
}

void Logger::_write(const QString &msg)
{
    if (!WRITE_IN_LOGFILE)
        return;

    if (_logFile == nullptr) {
        QDir dir(DEFAULT_LOG_DIR);
        if (dir.exists() == false)
            dir.mkpath(DEFAULT_LOG_DIR);
        _logFile = new QFile(_getLogFileName());
        if (_logFile->isOpen() == false)
        _logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        _write(QStringLiteral("---- NEW SESSION ----\n"));
    }

    _logFile->write(msg.toLocal8Bit() + '\n');
    _logFile->flush();
}

void Logger::_outputToStd(QtMsgType type, const QString& msg)
{
    switch (type) {
    case QtDebugMsg:
    case QtInfoMsg:
        std::cout << msg.toStdString() << std::endl;
        break;
    default:
        std::cerr << msg.toStdString();
        break;
    }
}

QString	Logger::_getLogFileName()
{
    return DEFAULT_LOG_DIR + "/" + DEFAULT_LOG_FILE + "_" + QDateTime::currentDateTime().toString("yyyyMMdd") + "." + DEFAULT_LOG_EXT;
}

QString	Logger::_getLogPrefix()
{
    return "<" + QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd-hh:mm:ss") + "> : ";
}
