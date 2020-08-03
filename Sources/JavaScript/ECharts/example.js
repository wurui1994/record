var fs = require('fs');
var jsdom = require("jsdom");
var jquery = require('jquery');
var echarts = require('echarts');

// {} 大括号构造器
var { JSDOM } = jsdom;
var html = '<div id="main" style="width:600px;height:400px"></div>';

global.window = new JSDOM(html).window;
global.document = window.document;

var $ = jquery(window);

// svg布局仅适合chrome,其他浏览器布局有问题。
// var chart = echarts.init(document.getElementById('main'), null, { renderer: 'svg' });
// var chart = echarts.init(document.getElementById('main'), null, { renderer: 'svg' });
var div = document.getElementById('main'); // jquery $ error.
var chart = echarts.init(div, null, { renderer: 'svg' });

eval(fs.readFileSync('./data.js','utf-8'));
chart.setOption(option);

// var data = chart.getDom().children[0].innerHTML;
// var data = document.getElementById('svg')[0].innerHTML;

var data = $("svg").parent().html();
fs.writeFileSync('./test.svg', data);
console.log("File write success.");
process.exit();