#!/usr/bin/python3
# -*- coding:utf-8 -*-
'''
本文件用于在编译时随机生成一个在asset文件夹中的测试json
放便对json库进行测试
'''
import json
import random
from utils import generate_random_str, generate_random_random

# 随机生成单层json
def generate_random_json():
    article_info = {}
    data = json.loads(json.dumps(article_info))
    for i in range(random.randint(1,20)):
        data[generate_random_str(random.randint(1,16))] = generate_random_random()
    return data
    

if __name__ == "__main__":
    data = generate_random_json()
    for i in range(random.randint(1,20)):
        data[generate_random_str(random.randint(1,16))] = generate_random_json()
    js = json.dumps(data, sort_keys=True, indent=4, separators=(',', ':'))
    with open('../asset/gen_json.json', 'wt') as f:
        print(js, file=f)

