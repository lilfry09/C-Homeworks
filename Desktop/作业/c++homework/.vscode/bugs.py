import requests
from bs4 import BeautifulSoup

# 目标URL
url = 'https://www.zhihu.com/'

# 发送HTTP请求
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.121 Safari/537.36'
}
response = requests.get(url, headers=headers)

# 检查请求是否成功
if response.status_code == 200:
    # 解析HTML内容
    soup = BeautifulSoup(response.content, 'html.parser')

    # 查找所有问题标题（假设问题标题在h2标签中）
    questions = soup.find_all('h2')
    
    # 打开文件以写入
    with open('zhihu_questions.txt', 'w', encoding='utf-8') as file:
        for question in questions:
            title = question.get_text(strip=True)
            file.write(title + '\n')
            print(title)
else:
    print(f"Failed to retrieve the page. Status code: {response.status_code}")

