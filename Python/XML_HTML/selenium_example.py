# from selenium import webdriver

# driver = webdriver.PhantomJS()
# driver.get('http://mtl.woatb.com/uploadfile/2017/0529/20170529104011317.jpg')
# data = driver.page_source
# print(data)
# driver.quit()

from selenium import webdriver
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities
 
dcap = dict(DesiredCapabilities.PHANTOMJS)  #设置userAgent
dcap["phantomjs.page.settings.userAgent"] = ("Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:25.0) Gecko/20100101 Firefox/25.0 ")
 
obj = webdriver.PhantomJS(desired_capabilities=dcap) #加载网址
obj.get('http://www.website.com/test.jpg')#打开网址
data = obj.page_source
print(data)
obj.save_screenshot("screenshot.png")   #截图保存
obj.quit()  # 关闭浏览器。当出现异常时记得在任务浏览器中关闭PhantomJS，因为会有多个PhantomJS在运行状态，影响电脑性能
