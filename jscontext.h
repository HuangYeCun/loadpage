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

		// ��JS������Ϣ
		void SendMsg(QWebEnginePage* page, const QString& msg);
		//���ʹ����
		void SendShipNum(QWebEnginePage* page, QString msg);
		//���������ļ�����
		void SendFileListRequest(QWebEnginePage* page, QString msg);
		//����Ҫ���ص��ļ�url
		void SendFileUrl(QWebEnginePage* page, QString msg);

	signals:
		//��Qt���ͽ��յ���msg�źţ����﷢�͵���loadpage��
        void recvd_filelist_signal(const QString& msg);
        //��Qt���ͽ��յ���msg�źţ��ؿ���Ƶ�������﷢�͵���loadpage��
        void recvd_lookback_filelist_signal(const QString& msg);
		void recvd_msg_signal(const QString& msg);

		public slots:
		// ���յ�ҳ�淢��������Ϣ������ҳ��js�����а�
		//���ղ�ѯ������Ϣ��ת�����ͣ�����/���ģ�
		void on_msg_slot(const QString& msg);
		//����Ҫ���ص��ļ��б�
		void on_receive_filelist_slot(const QString& msg);
        //����Ҫ�ؿ�����Ƶ�ļ��б�
        void on_receive_lookback_filelist_slot(const QString& msg);

	}; //class JsContext
}//namespace webengine

#endif // JSCONTEXT_H
