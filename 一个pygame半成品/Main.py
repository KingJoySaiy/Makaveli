# alien-invasion-game
from ship import *
from settings import Settings
from functions import *
from pygame.sprite import Group
from alien import Alien

def run_game():

    pygame.init()                           # 初始化游戏并创建一个屏幕对象
    ai_settings = Settings()                # 初始化设置
    screen = pygame.display.set_mode(       # 创建显示窗口,设置窗口尺寸
        (ai_settings.screen_width, ai_settings.screen_height))
    pygame.display.set_caption('KingJoy')   # 设置窗口名称
    ship = Ship(ai_settings,screen)
    bullets = Group()                       # 新建Group编组
    aliens = Alien(ai_settings,screen)
    # create_fleet(ai_settings,screen,aliens)

    while True:         # 开始游戏的主循环
        check_events(ai_settings,screen,ship,bullets)    # 更新操作事件
        ship.update()           # 更新ship对象
        update_bullets(bullets)        # 更新bullet对象
        update_screen(ai_settings,screen,ship,bullets,aliens)   # 更新屏幕显示

run_game()