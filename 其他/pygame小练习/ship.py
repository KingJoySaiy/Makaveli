import pygame
from pygame.sprite import Sprite

ship_speed = 1
class Ship:
    def __init__(self, ai_settings,screen):     # 初始化飞船并设置其初始位置
        self.screen = screen
        self.ai_settings = ai_settings

        self.image = pygame.image.load('images/ship.bmp')   # 加载飞船图像并获取其外接矩形
        self.rect = self.image.get_rect()
        self.screen_rect = screen.get_rect()

        self.rect.centerx = self.screen_rect.centerx  # 将每艘新飞船放在屏幕底部中央
        self.rect.bottom = self.screen_rect.bottom

        self.moving_right = False   # 设置移动标志
        self.moving_left = False
        self.moving_up = False
        self.moving_down = False
        self.x = float(self.rect.centerx)
        self.y = float(self.rect.centery)

    def built_me(self):             # 在指定位置绘制飞船
        self.screen.blit(self.image, self.rect)

    def update(self):
        if self.moving_right and self.rect.right < self.screen_rect.right:
            self.x += ship_speed
        if self.moving_left and self.rect.left > 0:
            self.x -= ship_speed
        if self.moving_up and self.rect.top > 0:
            self.y -= ship_speed
        if self.moving_down and self.rect.bottom < self.screen_rect.bottom:
            self.y += ship_speed

        self.rect.centerx = self.x
        self.rect.centery = self.y


class Bullet(Sprite): #一个对飞船发射的子弹进行管理的类
    def __init__(self, ai_settings, screen, ship): # 在飞船所处的位置创建一个子弹对象
        super(Bullet, self).__init__()
        self.screen = screen

        # 在(0,0)处创建一个表示子弹的矩形，再设置正确的位置
        self.rect = pygame.Rect(0,0,ai_settings.bullet_width,ai_settings.bullet_height)
        self.rect.centerx = ship.rect.centerx
        self.rect.top = ship.rect.top

        self.y = float(self.rect.y)     # 存储用小数表示的子弹位置
        self.color = ai_settings.bullet_color
        self.speed_factor = ai_settings.bullet_speed

    def update(self):       # 向上移动子弹
        self.y -= self.speed_factor     # 更新表示子弹位置的小数值
        self.rect.y = self.y            # 更新表示子弹的rect的位置

    def draw_bullet(self):  # 在屏幕上绘制子弹
        pygame.draw.rect(self.screen, self.color, self.rect)

