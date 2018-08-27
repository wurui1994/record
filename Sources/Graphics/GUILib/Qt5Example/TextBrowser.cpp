class TextEditC : public QTextBrowser
{
    Q_OBJECT

private:
    QString clickedAnchor;

public:
    TextEditC(QWidget *parent = 0) : QTextBrowser(parent)
    {
        //this->document()->setDefaultFont(QFont("Consolas", 14));
        //setTextInteractionFlags(Qt::LinksAccessibleByKeyboard | Qt::LinksAccessibleByMouse | Qt::TextBrowserInteraction | Qt::TextEditable | Qt::TextEditorInteraction | Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    }

    bool canInsertFromMimeData(const QMimeData *source) const
    {
        if (source->hasImage())
            return true;
        else
            return QTextEdit::canInsertFromMimeData(source);
    }


    void insertFromMimeData(const QMimeData *source)
    {
        qDebug() << source->formats();
        auto getFileMd5 =[](QString filePath)->QByteArray
        {
            QFile localFile(filePath);

            if (!localFile.open(QFile::ReadOnly))
            {
                qDebug() << "file open error.";
                return 0;
            }

            QCryptographicHash ch(QCryptographicHash::Md5);

            quint64 totalBytes = 0;
            quint64 bytesWritten = 0;
            quint64 bytesToWrite = 0;
            quint64 loadSize = 1024 * 4;
            QByteArray buf;

            totalBytes = localFile.size();
            bytesToWrite = totalBytes;

            while (1)
            {
                if (bytesToWrite > 0)
                {
                    buf = localFile.read(qMin(bytesToWrite, loadSize));
                    ch.addData(buf);
                    bytesWritten += buf.length();
                    bytesToWrite -= buf.length();
                    buf.resize(0);
                }
                else
                {
                    break;
                }

                if (bytesWritten == totalBytes)
                {
                    break;
                }
            }

            localFile.close();
            QByteArray md5 = ch.result();
            return md5;
        };

        if (source->hasImage() )
        {
            QString imageName;
            QImage image;
            //
            if(!source->hasUrls())
            {
                image = qvariant_cast<QImage>(source->imageData());
                imageName = "tmp.png";
                image.save(imageName);
            }
            else
            {
                imageName = source->urls().first().toLocalFile();
                image.load(imageName);
                
                QImage image = qvariant_cast<QImage>(source->imageData());

                //
                // QByteArray byteArray;
                // QBuffer buffer(&byteArray);
                // image.save(&buffer,"PNG");
                // image.save("test.bmp");
                // image.save("test.png");
                // QString pictureBase64 = QString::fromUtf8(byteArray.toBase64().data());
                // QCryptographicHash md5(QCryptographicHash::Md5);
                // md5.addData(pictureBase64.toUtf8());
                // QString imageMd5Name = md5.result().toHex().constData();
                // qDebug() << imageMd5Name;
            }
            qDebug() << imageName;
            qDebug() << image.hasAlphaChannel();
            //

            QString imageMd5Name = getFileMd5(imageName).toHex().constData();
            qDebug() << imageMd5Name;
            //
            document()->addResource(QTextDocument::ImageResource, QUrl(imageMd5Name), image);

            qDebug()<<"image";

            textCursor().insertImage(imageMd5Name);
            qDebug() << textCursor().block().document()->toHtml();
            //textCursor().insertHtml(html);
            //QTextEdit::insertFromMimeData(source);
        }
        else
        {
            QStringList format = source->formats();
            qDebug() << format;
            QString html = source->html();
            //QMessageBox::information(0, __FUNCTION__, html, 0);
            QDomDocument doc;
            doc.setContent(source->html());

            auto replaceTag=[](QDomDocument doc,QString oldTag,QString newTag)
            {
                QDomNodeList nodeList = doc.elementsByTagName(oldTag);
                for(int i=0;i<nodeList.size();++i)
                {
                    nodeList.at(i).toElement().setTagName(newTag);
                }
            };
            auto removeHref=[](QDomDocument doc)
            {
                QDomNodeList nodeList = doc.elementsByTagName("a");
                for(int i=0;i<nodeList.size();++i)
                {
                    nodeList.at(i).toElement().removeAttribute("href");
                }
            };

            if(doc.elementsByTagName("img").size() > 0
                    && !doc.elementsByTagName("img").at(0).toElement().attribute("src").startsWith("http")
                    && !doc.elementsByTagName("img").at(0).toElement().attribute("src").endsWith(".jpg")
                    && !doc.elementsByTagName("img").at(0).toElement().attribute("src").endsWith(".jpeg")
                    && !doc.elementsByTagName("img").at(0).toElement().attribute("src").endsWith(".gif")
                    && !doc.elementsByTagName("img").at(0).toElement().attribute("src").endsWith(".png"))
            {

                replaceTag(doc,"ul","p");
                replaceTag(doc,"li","p");
                replaceTag(doc,"h1","p");
                replaceTag(doc,"h2","p");
                replaceTag(doc,"h3","p");
                replaceTag(doc,"h4","p");
                replaceTag(doc,"h5","p");
                replaceTag(doc,"h6","p");
                removeHref(doc);

                textCursor().insertHtml(doc.toString());
            }
            else
            {
                textCursor().insertText(source->text());
            }
            qDebug()<<doc.toString();
        }
    }

    void mouseDoubleClickEvent(QMouseEvent *e)
    {
        bool s = textCursor().block().charFormat().isImageFormat();
        if (s)
        {
            QMessageBox::information(0, __FUNCTION__, 0, 0);
        }
        QTextEdit::mouseDoubleClickEvent(e);
    }

    void mousePressEvent(QMouseEvent *e)
    {
        auto cursor = cursorForPosition(e->pos());
        auto currentBlock = cursor.block();
        QTextBlock::iterator it;
        auto epos = e->pos();

        qDebug() << document()->blockCount();
        for (it = currentBlock.begin(); !(it.atEnd()); ++it)
        {

            QTextFragment fragment = it.fragment();
            if (fragment.isValid())
            {
                qDebug() << fragment.text();
                if (fragment.charFormat().isImageFormat())
                {
                    QTextImageFormat newImageFormat = fragment.charFormat().toImageFormat();
                    qDebug() << newImageFormat.anchorHref() << newImageFormat.name();
                    qDebug() << newImageFormat;
                    //int cw = cursorWidth();
                    qreal size = fragment.charFormat().fontPointSize();
                    int iw = newImageFormat.height();
                    int pos = cursor.position();
                    QRect r = cursorRect();
                    int fpos = fragment.position();
                    int bpos = cursor.positionInBlock();
                    bool isContain = fragment.contains(pos);
                    int len = fragment.length();
                    //bool isImage = currentCharFormat().isImageFormat();
                    if(pos == fpos )
                    {
                        QVariant res = this->document()->resource(QTextDocument::ImageResource, QUrl(newImageFormat.name()));
                        QImage img = res.value<QImage>();
                        qDebug() << img.size();
                        QMessageBox::information(0, newImageFormat.name(),__FUNCTION__, 0);
                        return ;
                        //newImageFormat.setName(QString("test.jpg"));
                        //QTextCursor helper = cursor;

                        //helper.setPosition(fragment.position());
                        //helper.setPosition(fragment.position() + fragment.length(),
                        //	QTextCursor::KeepAnchor);
                        //helper.setCharFormat(newImageFormat);
                    }
                }
            }
        }
        QTextEdit::mousePressEvent(e);
    }

signals:
    void linkActivated(QString);
};
