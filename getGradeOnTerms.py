#!/usr/bin/env python
# -*- coding: utf-8 -*-

import requests
from bs4 import BeautifulSoup

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

cook = {
    'Hm_lvt_41e71a1bb3180ffdb5c83f253d23d0c0': '1484801370',
    'JSESSIONID': 'abcq4YOU6A_66gRsYBoNv'
}
with open('cookies') as file:
    cook['JSESSIONID'] = file.read()

r = requests.get('http://jwxt.bupt.edu.cn/gradeLnAllAction.do?type=ln&oper=qbinfo',
                 cookies=cook,
                 headers=headers)

text = r.text
soup = BeautifulSoup(text, 'lxml')
r = soup.select('body > table[class="titleTop2"]')

with open('grade_term','w') as file:
    file.write('\n')
    for term in r:
        term = BeautifulSoup(str(term), 'lxml')
        term = term.select('tr > td > table > tr')
        # print(term)

        for lesson in term[:-1]:  # 去掉最后一项
            lesson = BeautifulSoup(str(lesson), 'lxml')
            lesson = lesson.select('tr > td ')
            for item in lesson:
                file.write(item.text.strip()+'\n')
#                print(item.text.strip())
#        print('\n学期分界线\n')
        file.write('\n\n')
    file.write('eof')
