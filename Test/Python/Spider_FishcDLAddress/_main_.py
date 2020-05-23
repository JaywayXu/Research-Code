import urllib.request as ur

def _print_(html,file,mod):

    asd = html.split('<title>')[:]

    title = asd[1].split('| 鱼C工作室</title>')[:][0]

    if '&#8211' in title:

        tit = title.split('&#8211;')[:][0] + "-" + title.split('&#8211;')[:][1]

    else:
        tit = title

    if mod in tit:

        add = html.split('密码：')[:]

        password = add[1][:4]

        address = add[0][-60:]

        ad = address.split("href=\"")[:]

        radd = ad[1][:].split("\" target=\"")[0]

        file.write('%-34s%-7s%s\n'%(radd,password,tit))

        print('%-34s%-7s%s'%(radd,password,tit))

with open("fishc_DLadr.txt","w") as f:

    low = int(input("输入最低数值(>0)："))

    high = int(input("输入最高数值(<7000)："))

    mod = input("输入要爬取的内容关键字：")

    for i in range(low,high):

        try:
            url = 'http://blog.fishc.com/'+str(i)+'.html#prettyPhoto/0/'

            resp = ur.urlopen(url)

            html = resp.read().decode('utf-8')

            if "密码：" in html:

                _print_(html,f,mod)

            else:
                url = 'http://blog.fishc.com/'+str(i)+'.html/2#prettyPhoto/0/'

                resp = ur.urlopen(url)

                html = resp.read().decode('utf-8')

                if "密码：" in html:

                    _print_(html,f,mod)

                else:
                    continue

        except:
            continue