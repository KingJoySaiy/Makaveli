class Settings:         # 初始化游戏的设置
    def __init__(self):
        self.screen_width = 800             # 设置窗口宽度
        self.screen_height = 600            # 设置窗口高度
        self.bg_color = (230, 230, 230)     # 设置背景色(参数为RGB值)

        self.bullet_speed = 1               # 设置子弹属性
        self.bullet_width = 3
        self.bullet_height = 10
        self.bullet_color = (30,30,30)
        self.bullets_allowed = 6             # 设置子弹数量


