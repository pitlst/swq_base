#!/usr/bin/python3
# -*- coding:utf-8 -*-
'''
本文件用于在编译时随机生成一个在asset文件夹中的测试xml
放便对xml库进行测试
'''
import random
from xml.etree import ElementTree
from utils import generate_xml_str, generate_random_random

count = 0

# 随机生成单层xml
def generate_random_xml():
    global count
    count += 1
    root = ElementTree.Element(generate_xml_str(random.randint(0,16)))
    for i in range(random.randint(0,20)):
        head = ElementTree.SubElement(root, generate_xml_str(random.randint(0,16)))
        if random.randint(0,1) and count < 10:
            head.append(generate_random_xml())
        else:
            head.text = str(generate_random_random())
    return root

# elemnt为传进来的Elment类，参数indent用于缩进，newline用于换行   
def prettyXml(element, indent, newline, level = 0): 
    # 判断element是否有子元素
    if element:
        # 如果element的text没有内容      
        if element.text == None or element.text.isspace():     
            element.text = newline + indent * (level + 1)      
        else:    
            element.text = newline + indent * (level + 1) + element.text.strip() + newline + indent * (level + 1)    
    # 此处两行如果把注释去掉，Element的text也会另起一行 
    #else:     
        #element.text = newline + indent * (level + 1) + element.text.strip() + newline + indent * level    
    temp = list(element) # 将elemnt转成list    
    for subelement in temp:    
        # 如果不是list的最后一个元素，说明下一个行是同级别元素的起始，缩进应一致
        if temp.index(subelement) < (len(temp) - 1):     
            subelement.tail = newline + indent * (level + 1)    
        else:  # 如果是list的最后一个元素， 说明下一行是母元素的结束，缩进应该少一个    
            subelement.tail = newline + indent * level   
        # 对子元素进行递归操作 
        prettyXml(subelement, indent, newline, level = level + 1)   

if __name__ == "__main__":
    root = generate_random_xml()
    prettyXml(root, '\t', '\n')
    data = ElementTree.ElementTree(root)
    data.write('../asset/gen_xml.xml', encoding = 'utf-8', xml_declaration=True)