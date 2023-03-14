#!/usr/bin/python3
# -*- coding:utf-8 -*-
'''
本文件用于在编译时随机生成一个在asset文件夹中的测试ini
放便对ini库进行测试
'''

import random
from utils import generate_random_str, generate_random_random

def generate_random_ini():
    section = "[" + generate_random_str() + "]\n"
    for i in range(random.randint(0,10)):
        section += (generate_random_str() + "=" + str(generate_random_random()) + "\n")
        if random.randint(0,1):
            section += (";" + str(generate_random_random()) + "\n")
    return section
if __name__ == "__main__":
    need_str = ""
    for i in range(random.randint(1,10)):
        need_str += (generate_random_ini() + "\n")
        if random.randint(0,1):
            need_str += (";" + str(generate_random_random()) + "\n")
    with open('../asset/gen_ini.ini', 'wt') as f:
        print(need_str, file=f)