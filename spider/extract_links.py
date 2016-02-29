#-*-coding:utf8-*-

import sys
import urllib
import urllib2
import urlparse
import re

from BeautifulSoup import BeautifulSoup

class MyOpener(urllib.FancyURLopener):
    #version = 'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.2.15) Gecko/20110303 Firefox/3.6.15'
    version = 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36'

def process(url):
    myopener = MyOpener()
    page = myopener.open(url)
    
    # req = urllib2.Request(url)
    # req.add_header('User-Agent', 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36')
    # req.add_header('cookie', 'bid=damn')
    # page = urllib2.urlopen(req)

    text = page.read()
    #print text
    page.close()
    soup = BeautifulSoup(text)
    urls = []
    for tag in soup.findAll('a', href=True):
        tag['href'] = urlparse.urljoin(url, tag['href'])
        urls.append(tag['href'])
    return urls

def main():
    urls_queue = sys.argv[1:] 
    urls_found = []
    urls_done = []
    site_roots = []

    for url in urls_queue:
        mre = re.match('^https?://[^/]*',url,re.IGNORECASE)
        if mre:
            site_roots.append( mre.group(0) )
            print mre.group(0) ####################
            print '---------------------' ##########################

    while len(urls_queue) > 0:
        url = urls_queue.pop()
        urls_done.append(url)

        found = process(url)

        for uf in found:
            if not any( [ uf.startswith( site_root ) for site_root in site_roots ] ):
                continue 

            if uf not in urls_found:
                urls_found.append(uf) 

            if uf not in urls_queue and uf not in urls_done:
                urls_queue.append(uf)

        print "Done %d; Queued %d; Found %d" % ( len(urls_done), len(urls_queue), len(urls_found) )

    print '---------------------' ##########################
    print urls_found

if __name__ == "__main__":
    main()
    
