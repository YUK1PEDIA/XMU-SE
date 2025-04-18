(function(d, s, id) {
	var iframe;
	if (d.getElementById(id)) return;
	iframe = d.createElement(s);
	iframe.id = id;
	iframe.src = '//d' + Math.floor(0 + Math.random() * (9 - 0 + 1)) + '.sina.com.cn/litong/zhitou/sinaads/src/spec/sinaads_ck.html';
	iframe.style.display = 'none';
	d.body.appendChild(iframe);
})(document, 'iframe', 'sinaads-ck-iframe');