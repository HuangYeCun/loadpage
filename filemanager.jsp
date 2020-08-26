<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>

<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions"%>
<c:set var="ctx" value="${pageContext.request.contextPath}" />
<!DOCTYPE html>
<html>
<head>

<jsp:include page="../inc.jsp"></jsp:include>
<meta http-equiv="X-UA-Compatible" content="edge" />
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>文件下载管理</title>

<script type="text/javascript" src="${ctx}/js/webchannel/qwebchannel.js"></script>
<script type="text/javascript" src="${ctx}/js/webchannel/jsmsg.js"></script>
<script type="text/javascript">
	var dataGrid;
	$(function() {
		dataGrid = $('#dataGrid').datagrid({
			url : '${ctx}/filemanager/fileDataGrid',
			// 							url : '${ctx}/filemanager/dataGrid',
			striped : true,
			rownumbers : true,
			pagination : true,
			singleSelect : true,
			idField : 'uuid',
			sortName : 'updatetime',
			sortOrder : 'desc',
			pageSize : 50,
			pageList : [ 10, 20, 30, 40, 50, 100, 200, 300, 400, 500 ],
			columns : [ [ {
				width : '500',
				title : '文件名',
				field : 'filename',
				sortable : false
			}, {
				width : '150',
				title : '大小',
				field : 'filesize',
				sortable : false
			},
			// 						{
			// 							width : '250',
			// 							title : '日期',
			// 							field : 'filemodifytime',
			// 							sortable : true
			// 						},
			] ],
			toolbar : '#toolbar'
		});
	});

	function searchFun() {
		if (!JudgeQueryCondition()) {
			return false;
		}
		//查询本地路径下的文件
		dataGrid.datagrid('load', $.serializeObject($('#searchForm')));
		return true;
	}
	function cleanFun() {
		// 		$('#searchForm input').val('');
		$("input[name='cameranum']").val('');
		$("input[name='timeStart']").val('');
		$("input[name='timeEnd']").val('');

		document.getElementById("sp_cam").innerText = "";
		document.getElementById("sp_time").innerText = "";
		$("input[name='cameranum']").css('borderColor', ''); //添加css样式
		$("input[name='timeStart']").css('borderColor', ''); //添加css样式
		$("input[name='timeEnd']").css('borderColor', ''); //添加css样式

		dataGrid.datagrid('load', {});
	}

	// 接收qt发送的船编号,json格式
	function recvShipnum(msg) {
		var result_json = JSON.parse(msg);
		var shipnum = result_json['shipnum'];

		$("#shipnum").attr("value", shipnum);
		$("#shipnum").attr("onfocus", "this.blur()"); //禁止选择input中的文字
		$("#shipnum").css("background", "#CCCCCC"); //背景为灰色
		$("#shipnum").css("cursor", "not-allowed"); //鼠标滑动到input上，出现禁止操作图标
	}

	function JudgeQueryCondition() {
		return JudgeCamera() & JudgeDate();
	}
	
	function JudgeCamera() {
		//校验船舶编号格式
		var cameranum = $("input[name='cameranum']").val();
		var pattText = /^[0-9a-zA-Z_]{1,}$/;
		if (pattText.test(cameranum) || cameranum == '') {
			$("input[name='cameranum']").css('borderColor', ''); //添加css样式
			document.getElementById("sp_cam").innerText = "";
			// 			document.getElementById("sp_cam").style.color="green";
			return true;
		} else {
			document.getElementById("sp_cam").innerText = "摄像头编号由数字、字母、下划线组成";
			document.getElementById("sp_cam").style.color = "red";
			$("input[name='cameranum']").css('borderColor', '#FF6633'); //添加css样式
			return false;
		}
	}
	
	function JudgeDate() {
		//校验日期，日期不能只有一个，开始日期不能大于结束日期
		var timestart = $("input[name='timeStart']").val();
		var timeend = $("input[name='timeEnd']").val();

		if (timestart == '' && timeend != '') {
			document.getElementById("sp_time").innerText = "请输入开始时间";
			document.getElementById("sp_time").style.color = "red";
			$("input[name='timeStart']").css('borderColor', '#FF6633'); //添加css样式
			$("input[name='timeEnd']").css('borderColor', ''); //添加css样式
			return false;
		}
		if (timestart != '' && timeend == '') {
			document.getElementById("sp_time").innerText = "请输入结束时间";
			document.getElementById("sp_time").style.color = "red";
			$("input[name='timeStart']").css('borderColor', ''); //添加css样式
			$("input[name='timeEnd']").css('borderColor', '#FF6633'); //添加css样式
			return false;
		}
		if (timestart != '' && timeend != '') {
			//开始时间大于结束时间，则错误
			var timestart_parse = new Date(Date.parse(timestart));
			var timeend_parse = new Date(Date.parse(timeend));
			if (timestart_parse > timeend_parse) {
				document.getElementById("sp_time").innerText = "请确保开始时间小于结束时间";
				document.getElementById("sp_time").style.color = "red";
				$("input[name='timeStart']").css('borderColor', '#FF6633'); //添加css样式
				$("input[name='timeEnd']").css('borderColor', ''); //添加css样式
				return false;
			}
		}
		//时间可同时为空；同时不为空时，开始时间小于结束时间
		document.getElementById("sp_time").innerText = "";
		$("input[name='timeStart']").css('borderColor', ''); //添加css样式
		$("input[name='timeEnd']").css('borderColor', ''); //添加css样式

		return true;
	}

	function StartConvert(msg) {
		if (!searchFun())
			return;

		sendmsg(msg);
	}

	function lookback() {
		//发送查询条件
		if(!searchFun())
			return;

		var shipnum = $("input[name='shipnum']").val();
		var cameranum = $("input[name='cameranum']").val();
		var timeStart = $("input[name='timeStart']").val();
		var timeEnd = $("input[name='timeEnd']").val();

		$.ajax({
			url : '${ctx}/filemanager/getlookbackfile?shipnum=' + shipnum
					+ '&cameranum=' + cameranum + '&timeStart=' + timeStart
					+ '&timeEnd=' + timeEnd,
			method : 'post',
			success : function(result) {
				sendLookbackFileList(result);
			},
			failure : function() {
			}
		});
	}

	function GetDownloadFile() {
		var shipnum = $("input[name='shipnum']").val();
		var cameranum = $("input[name='cameranum']").val();
		var timeStart = $("input[name='timeStart']").val();
		var timeEnd = $("input[name='timeEnd']").val();

		$.ajax({
			url : '${ctx}/filemanager/getdownloadfile?shipnum=' + shipnum
					+ '&cameranum=' + cameranum + '&timeStart=' + timeStart
					+ '&timeEnd=' + timeEnd,
			method : 'post',
			success : function(result) {
				sendFileList(result);
			},
			failure : function() {
			}
		});
	}

	// 接收qt申请下载文件url请求
	function recvFilelistReq(msg) {
		var result_json = JSON.parse(msg);
		var state = result_json['state'];

		GetDownloadFile();
	}

	function DownloadFile(fileurl) {
		var voiceUrl = '${ctx}/filemanager/download?fileurl=' + fileurl;
// 		alert(voiceUrl);

		var iframe = document.createElement("iframe");
		document.body.appendChild(iframe);
		iframe.src = voiceUrl;
		iframe.style.display = "none";
		iframe.method = "post";
		setTimeout(function() {
			iframe.remove();
		}, 1 * 60 * 1000);
	}

	// 接收qt申请下载文件url请求
	function recvFileUrl(msg) {	
// 		alert(msg);
		msg=msg.replace(/\\/g,'\\\\');
		var result_json = JSON.parse(msg);
		var fileurl = result_json['fileurl'];
// 		alert(fileurl);

		DownloadFile(fileurl);
	}
	
	
</script>
</head>
<body class="easyui-layout" data-options="fit:true,border:false">
	<div data-options="region:'north',border:false"
		style="height: 30px; overflow: hidden; background-color: #f4f4f4">
		<form id="searchForm">
			<table>
				<tr>
					<th>船舶编号:</th>
					<td><input id="shipnum" name="shipnum" placeholder="请输入船舶编号" /></td>
					<th>摄像头编号:</th>
					<td><input type="text" name="cameranum" placeholder="请输入摄像头编号" /><span
						id="sp_cam"></span></td>
					<th>时间:</th>
					<td><input name="timeStart" placeholder="点击选择时间"
						onclick="WdatePicker({readOnly:true,dateFmt:'yyyy-MM-dd HH:00:00'})"
						readonly="readonly" />至<input name="timeEnd" placeholder="点击选择时间"
						onclick="WdatePicker({readOnly:true,dateFmt:'yyyy-MM-dd HH:00:00'})"
						readonly="readonly" /><span id="sp_time"></span> <a
						href="javascript:void(0);" class="easyui-linkbutton"
						data-options="iconCls:'icon_search',plain:true"
						onclick="searchFun();">查询</a><a href="javascript:void(0);"
						class="easyui-linkbutton"
						data-options="iconCls:'icon_cancel',plain:true"
						onclick="cleanFun();">清空</a>
						<a href="javascript:void(0);"
						class="easyui-linkbutton"
						data-options="iconCls:'icon_cancel',plain:true"
						onclick="comTest();">COM测试</a></td>
				</tr>
			</table>

		</form>
	</div>
	<div data-options="region:'center',border:false,title:'文件列表'">
		<table id="dataGrid" data-options="fit:true,border:false"></table>
	</div>
	<div id="toolbar" style="display: none;">
		<c:if test="${fn:contains(sessionInfo.resourceList, '')}">
			<!--  			str += $.formatString('<a href="javascript:void(0)" onclick="downloadFun(\'{0}\');" >下载文件</a>', row.uuid); -->
			<a onclick="StartConvert('ciphertext');" href="javascript:void(0);"
				class="easyui-linkbutton"
				data-options="plain:true,iconCls:'icon_folder'">密文转存</a>
		</c:if>
		<c:if test="${fn:contains(sessionInfo.resourceList, '')}">
			<a onclick="StartConvert('plaintext');" href="javascript:void(0);"
				class="easyui-linkbutton"
				data-options="plain:true,iconCls:'icon_folder'">明文转存</a>
		</c:if>
		<c:if test="${fn:contains(sessionInfo.resourceList, '')}">
			<a onclick="lookback();" href="javascript:void(0);"
				class="easyui-linkbutton"
				data-options="plain:true,iconCls:'icon_resource'">回看</a>
		</c:if>
	</div>
</body>
</html>