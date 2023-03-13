import json
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

