import sys
import pygame
from ship import Bullet
from alien import Alien

def fire_bullet(ai_setting,screen,ship,bullets):
    if len(bullets) < ai_setting.bullets_allowed:  # 限制bullet个数
        new_bullet = Bullet(ai_setting, screen, ship)
        bullets.add(new_bullet)

def check_keydown_event(event,ai_setting,screen,ship,bullets):
    if event.key == pygame.K_RIGHT:
        ship.moving_right = True
    elif event.key == pygame.K_LEFT:
        ship.moving_left = True
    elif event.key == pygame.K_UP:
        ship.moving_up = True
    elif event.key == pygame.K_DOWN:
        ship.moving_down = True
    elif event.key == pygame.K_SPACE:
        fire_bullet(ai_setting,screen,ship,bullets)
    elif event.key == pygame.K_BACKSPACE:       # 按下Backspace关闭游戏
        sys.exit()

def check_keyup_event(event,ship):
    if event.key == pygame.K_RIGHT:
        ship.moving_right = False
    elif event.key == pygame.K_LEFT:
        ship.moving_left = False
    elif event.key == pygame.K_UP:
        ship.moving_up = False
    elif event.key == pygame.K_DOWN:
        ship.moving_down =False

def check_events(ai_setting,screen,ship,bullet):     # 响应按键和鼠标事件
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            check_keydown_event(event,ai_setting,screen,ship,bullet)
        elif event.type == pygame.KEYUP:
            check_keyup_event(event,ship)

def update_screen(ai_settings,screen,ship,bullets,aliens): # 更新屏幕
    screen.fill(ai_settings.bg_color)       # 每次循环都重新绘制屏幕

    for bullet in bullets.sprites():        # 重绘所有的bullet对象
        bullet.draw_bullet()
    ship.built_me()                         # 创建ship对象
    aliens.built_me()                        # 创建alien对象
    pygame.display.flip()           # 让最近绘制的屏幕可见

def update_bullets(bullets):        # 更新bullet对象
    bullets.update()
    for bullet in bullets.copy():   # 删除走出屏幕的bullet对象
        if bullet.rect.bottom <= 0:
            bullets.remove(bullet)
        print(len(bullets))

# def create_fleet(ai_settings, screen, aliens):  # 创建aliens群
#
#     # 创建一个外星人，并计算一行可容纳多少个外星人
#     # 外星人间距为外星人宽度
#     alien = Alien(ai_settings, screen)
#     alien_width = alien.rect.width
#     available_space_x = ai_settings.screen_width - 2 * alien_width
#     number_aliens_x = int(available_space_x / (2 * alien_width))
#
#     # 创建第一行aliens
#     for alien_number in range(number_aliens_x):
#         alien = Alien(ai_settings, screen)
#         alien.x = alien_width + 2 * alien_width * alien_number
#         alien.rect.x = alien.x
#         aliens.add(alien)