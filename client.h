#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

enum class LANGUAGE //语言包,这个放到客户端更合适
{
    CHINESE,//中文
    ENGLISH//英文
};

class Client : public QObject//客户端类
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

signals:

public slots:

private:


public:
    void login();//登陆
    void setLanguage(LANGUAGE language);//改变语言，把这个放到客户端的程序

};

#endif // CLIENT_H
