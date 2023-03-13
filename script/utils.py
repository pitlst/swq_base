#!/usr/bin/python3
# -*- coding:utf-8 -*-
import random

base_str = "ABCDEFGHIGKLMNOPQRSTUVWXYZabcdefghigklmnopqrstuvwxyz0123456789"
max_int = 2147483647
min_int = -2147483648


# 随机生成字符串
def generate_random_str(randomlength = 16):
    # randomlength 是生成值的长度
    random_str = ''
    length = len(base_str) - 1
    for i in range(randomlength):
        random_str += base_str[random.randint(0, length)]
    return random_str

# 随机生成变量
def generate_random_random(temp = 0):
    if temp == 0:
        temp = random.randint(1,5)
    if temp == 1:
        return random.randint(min_int,max_int)
    elif temp == 2:
        return random.random()*random.randint(min_int,max_int)
    elif temp == 3:
        return generate_random_str(random.randint(1,16))
    elif temp == 4:
        tmp = random.random()
        if tmp > 0.5:
            return False
        else:
            return True
    elif temp == 5:
        return None
    else:
        return generate_random_random()