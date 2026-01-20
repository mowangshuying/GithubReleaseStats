#pragma once

#include <QList>
#include <QString>

class ReleaseInfo
{
  public:
    ReleaseInfo()
    {
    }
    ReleaseInfo(QString publishedOn, QString releaseAuthor, int downloads)
    {
        m_publishedOn = publishedOn;
        m_releaseAuthor = releaseAuthor;
        m_downloads = downloads;
    }

    QString getPublishedOn()
    {
        return m_publishedOn;
    }

    QString getReleaseAuthor()
    {
        return m_releaseAuthor;
    }

    int getDownloads()
    {
        return m_downloads;
    }

    void setPublishedOn(QString publishedOn)
    {
        m_publishedOn = publishedOn;
    }

    void setReleaseAuthor(QString releaseAuthor)
    {
        m_releaseAuthor = releaseAuthor;
    }

    void setDownloads(int downloads)
    {
        m_downloads = downloads;
    }

  protected:
    QString m_publishedOn;
    QString m_releaseAuthor;
    int m_downloads;
};

class DownloadInfo
{
  public:
    DownloadInfo()
    {
    }
    DownloadInfo(QString name, QString size, QString lastUpdated, int downloadCount, QString browserDownloadUrl)
    {
        m_name = name;
        m_size = size;
        m_lastUpdated = lastUpdated;
        m_downloadCount = downloadCount;
        m_browserDownloadUrl = browserDownloadUrl;
    }

    QString getName()
    {
        return m_name;
    }

    QString getSize()
    {
        return m_size;
    }

    QString getLastUpdated()
    {
        return m_lastUpdated;
    }

    int getDownloadCount()
    {
        return m_downloadCount;
    }

    void setName(QString name)
    {
        m_name = name;
    }

    void setSize(QString size)
    {
        m_size = size;
    }

    void setLastUpdated(QString lastUpdated)
    {
        m_lastUpdated = lastUpdated;
    }

    void setDownloadCount(int downloadCount)
    {
        m_downloadCount = downloadCount;
    }

    QString getBrowserDownloadUrl()
    {
        return m_browserDownloadUrl;
    }

    void setBrowserDownloadUrl(QString browserDownloadUrl)
    {
        m_browserDownloadUrl = browserDownloadUrl;
    }

  protected:
    QString m_name;
    QString m_size;
    QString m_lastUpdated;
    int m_downloadCount;
    QString m_browserDownloadUrl;
};

class Info
{
  public:
    Info()
    {
    }

    Info(QString tagName, ReleaseInfo releaseInfo, QList<DownloadInfo> downloadInfos)
    {
        m_tagName = tagName;
        m_releaseInfo = releaseInfo;
        m_downloadInfos = downloadInfos;
    }

    QString getTagName()
    {
        return m_tagName;
    }

    ReleaseInfo getReleaseInfo()
    {
        return m_releaseInfo;
    }

    QList<DownloadInfo> getDownloadInfos()
    {
        return m_downloadInfos;
    }

    void setTagName(QString tagName)
    {
        m_tagName = tagName;
    }

    void setReleaseInfo(ReleaseInfo releaseInfo)
    {
        m_releaseInfo = releaseInfo;
    }

    void setDownloadInfos(QList<DownloadInfo> downloadInfos)
    {
        m_downloadInfos = downloadInfos;
    }

  protected:
    QString m_tagName;
    ReleaseInfo m_releaseInfo;
    QList<DownloadInfo> m_downloadInfos;
};
