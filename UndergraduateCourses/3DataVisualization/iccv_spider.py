import re
import requests

url = "http://openaccess.thecvf.com/ICCV2019.py"
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.92 Safari/537.36"}
res = requests.get(url, headers=headers)
res.encoding = "utf-8"

title_authorStr_list = re.findall(
    """<dt class="ptitle"><br><a href=".*?">(.*?)</a>.*?</dt>.<dd>(.*?)</dd>""", res.text, re.S)

title_author_list = []

for title, authorStr in title_authorStr_list:
    author = re.findall("""value="(.*?)">""", authorStr, re.S)

    title_author_list.append((title, author))

title_author_file = open("iccv_title_author.txt", "w")

for title, author_list in title_author_list:
    print(title, file=title_author_file)
    author_str = ""
    for author in author_list:
        author_str = author_str + author + ","
    print(author_str, file=title_author_file)
