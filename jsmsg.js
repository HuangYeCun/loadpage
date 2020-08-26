var context;
// 初始化
function init() {
	if (typeof qt != 'undefined') {
		new QWebChannel(qt.webChannelTransport, function(channel) {
			context = channel.objects.context;
		});
	} else {
		alert("qt对象获取失败！");
	}
}
// 向qt发送消息
function sendMessage(msg) {
	if (typeof context == 'undefined') {
		alert("context对象获取失败！");
	} else {
		// 绑定QT接收消息的接口
		context.on_msg_slot(msg);
	}
}

function sendFileList(msg) {
	if (typeof context == 'undefined') {
		alert("context对象获取失败！");
	} else {
		// 绑定QT接收消息的接口
		context.on_receive_filelist_slot(msg);
	}
}

//向qt发送回看的视频列表消息
function sendLookbackFileList(msg) {
	if (typeof context == 'undefined') {
		alert("context对象获取失败！");
	} else {
		// 绑定QT接收消息的接口
		context.on_receive_lookback_filelist_slot(msg);
	}
}

// 控件控制函数
function sendmsg(msg) {
	var shipnum = $("input[name='shipnum']").val();
	var cameranum = $("input[name='cameranum']").val();
	var timestart = $("input[name='timeStart']").val();
	var timeend = $("input[name='timeEnd']").val();
	var queryCondition = shipnum + cameranum + timestart + timeend;

	var sendjson = '{"address":"", "shipNum":"' + shipnum + '", "cameraNum":"'
			+ cameranum + '", "beginTime":"' + timestart + '", "endTime":"'
			+ timeend + '", "type":"' + msg + '" }';

	//发送查询条件,type是明文/密文
	sendMessage(sendjson);
}

init();
