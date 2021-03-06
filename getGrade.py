#!/usr/bin/env python
# -*- coding: utf-8 -*-
import requests
from bs4 import BeautifulSoup

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

with open('cookies') as file: #  读取cookies
    cook['JSESSIONID'] = file.read()


r = requests.get('http://jwxt.bupt.edu.cn/gradeLnAllAction.do?type=ln&oper=fainfo',
                         cookies=cook,
                         headers=headers)

soup = BeautifulSoup(r.text, "lxml")
info = soup.find_all('tr', class_='odd')


with open('grade','w') as file:
    file.write('\n')
    for lesson in info:
        lesson = BeautifulSoup(str(lesson), 'lxml')
        lesson = lesson.select('td')
        item=[]
        for column in lesson:
            column = BeautifulSoup(str(column), 'lxml')
            column = column.text.strip()
            item.append(column)
            if column=='':
                column='-'
            file.write(column+'\n')
    file.write('eof\n')

print('Grades Got!')
