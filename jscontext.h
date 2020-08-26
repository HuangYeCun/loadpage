#ifndef JSCONTEXT_H
#define JSCONTEXT_H

#include <QObject>

class QWebEnginePage;

namespace webengine {

	class JsContext : public QObject {
		Q_OBJECT

	public:
		JsContext(QObject *parent);
		~JsContext();

		// 向JS发送消息
		void SendMsg(QWebEnginePage* page, const QString& msg);
		//发送船编号
		void SendShipNum(QWebEnginePage* page, QString msg);
		//发送下载文件请求
		void SendFileListRequest(QWebEnginePage* page, QString msg);
		//发送要下载的文件url
		void SendFileUrl(QWebEnginePage* page, QString msg);

	signals:
		//向Qt发送接收到的msg信号，这里发送到了loadpage层
        void recvd_filelist_signal(const QString& msg);
        //向Qt发送接收到的msg信号（回看视频），这里发送到了loadpage层
        void recvd_lookback_filelist_signal(const QString& msg);
		void recvd_msg_signal(const QString& msg);

		public slots:
		// 接收到页面发送来的消息，在网页端js方法中绑定
		//接收查询条件消息和转存类型（明文/密文）
		void on_msg_slot(const QString& msg);
		//接收要下载的文件列表
		void on_receive_filelist_slot(const QString& msg);
        //接收要回看的视频文件列表
        void on_receive_lookback_filelist_slot(const QString& msg);

	}; //class JsContext
}//namespace webengine

#endif // JSCONTEXT_H
