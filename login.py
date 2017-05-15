#!/usr/bin/env python
# -*- coding: utf-8 -*-
import requests
from bs4 import BeautifulSoup

data = {
    'type': 'sso',
    'zjh': '**********',
    'mm': '******',
    'v_yzm': '****'
}

cook = {
    'Hm_lvt_41e71a1bb3180ffdb5c83f253d23d0c0': '1484801370',
    'JSESSIONID': '*********************'
}

headers = {
    'Host': 'jwxt.bupt.edu.cn',
    'Connection': 'keep-alive',
    'Content-Length': '48',
    'Cache-Control': 'max-age=0',
    'Origin': 'http://jwxt.bupt.edu.cn',
    'Upgrade-Insecure-Requests': '1',
    'User-Agent': 'Mozilla/5.0 (X11; Fedora; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
    'Content-Type': 'application/x-www-form-urlencoded',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Referer': 'http://jwxt.bupt.edu.cn',
    'Accept-Encoding': 'gzip, deflate',
    'Accept-Language': 'zh-CN,zh;q=0.8,en;q=0.6',
    # 'Cookie': 'Hm_lvt_41e71a1bb3180ffdb5c83f253d23d0c0=1484801370; JSESSIONID=abcA57SnxXC4p6cXtjlNv'
}

with open('loginInfo') as file: #  读取登录信息
    data['zjh']=file.readline().strip()
    data['mm']=file.readline().strip()
    data['v_yzm']=file.readline().strip()

with open('cookies') as file: #  读取cookies
    cook['JSESSIONID']=file.readline()

r = requests.post('http://jwxt.bupt.edu.cn/jwLoginAction.do',
    data=data,
    cookies=cook,
    headers=headers)

soup = BeautifulSoup(r.text, "lxml")
#print(soup.title.text)
flag=False
if soup.title.text == '学分制综合教务':
    flag=True
    print('登录成功')

with open('loginResult','w') as file: #  写登录结果
    file.write(str(flag))
