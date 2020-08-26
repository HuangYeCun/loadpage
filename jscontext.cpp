#include "jscontext.h"

#include <QWebEnginePage>

#include "LogWorker.h"

namespace webengine {

	JsContext::JsContext(QObject *parent)
		: QObject(parent) {
		LOG_INF << "����JsContext";
	}

	JsContext::~JsContext() {
		LOG_INF << "����JsContext";
	}


	void JsContext::SendMsg(QWebEnginePage* page, const QString& msg) {
		page->runJavaScript(QString("recvMessage('%1');").arg(msg));
	}

	void JsContext::SendShipNum(QWebEnginePage* page, QString msg) {
		page->runJavaScript(QString("recvShipnum('%1');").arg(msg));
	}

	void JsContext::SendFileListRequest(QWebEnginePage* page, QString msg) {
		page->runJavaScript(QString("recvFilelistReq('%1');").arg(msg));
	}

	void JsContext::SendFileUrl(QWebEnginePage* page, QString msg) {
		page->runJavaScript(QString("recvFileUrl('%1');").arg(msg));
	}

	void JsContext::on_receive_filelist_slot(const QString& msg) {
		Q_EMIT recvd_filelist_signal(msg);
	}

    //����Ҫ�ؿ�����Ƶ�ļ��б�
    void JsContext::on_receive_lookback_filelist_slot(const QString& msg){
        Q_EMIT recvd_lookback_filelist_signal(msg);
    }

	void JsContext::on_msg_slot(const QString &msg) {
		Q_EMIT recvd_msg_signal(msg);
	}

}//namespace webengine
