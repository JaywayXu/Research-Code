import re  # 用于在网页中搜索我们需要的关键字
import requests  # 用于获取网页


# 抓取页码内容，返回响应对象
response = requests.get(
    'https://www.sohu.com/a/398546912_362042?code=20da3c90b724f777b6c34d63ae9bf8b2&spm=smpc.home.top-news1.1.1590775714572LWVOB4d&_f=index_cpc_0')
text = response.content.decode()

text = re.sub('<script[\s\S]*?>[\s\S]*?</script>', '', text)
text = re.sub(r"<[\s\S]*?>", "", text)  # 去除标签
text = re.sub(r"\s+", "", text)  # 去除空白字符

print(text)
