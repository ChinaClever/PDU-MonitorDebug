from ctrlset_ip.ip_web import  *

class IpV1(IpWeb):

    def start_fun(self):
        self.login()
        self.setCorrect()
        self.setEle()
        self.setThreshold()
        #self.resetFactory()
        self.driver.quit()

    def setCorrect(self):
        cfg = self.cfgs
        ip =  self.ip_prefix + cfg['ip'] + '/correct.html'
        self.driver.get(ip); time.sleep(1)
        self.driver.switch_to.default_content()
        self.setItById("language", int(cfg['ip_language'])+1, '设备语言')
        self.setItById("modbus", cfg['ip_modbus'], '设备模式')
        self.setItById("lcdled", cfg['ip_lines'], '设备相数')
        self.setItById("ACDC", cfg['ip_ac'], '交直流')
        self.setItById("horizontal", cfg['lcd_switch'], '新旧屏')
        if(len(cfg['mac']) > 5) :
            self.setItById("mac1", cfg['mac'], 'Mac地址')
        self.alertClick("Button3")
        self.sendtoMainapp("设备后台网页配置成功", 1)
        self.driver.back()
        time.sleep(0.5)
    
    








