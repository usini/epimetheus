from css_html_js_minify import html_minify, css_minify
from jsmin import jsmin
import os
import shutil

files = os.listdir("./")
for f in files:
  ext = os.path.splitext(f)[1]
  with open(f, 'r', encoding="utf8") as webfile:
    web_raw = webfile.read()
    if ext == ".css":
      print(f + " ... CSS")
      css_minified = css_minify(web_raw).replace('@charset "utf-8";','')
      with open("../data/" + f, "w", encoding="utf8") as css_new:
          css_new.write(css_minified)
    if ext == ".js":
      print(f + " ... JS")  
      js_minified = jsmin(web_raw).replace('@charset "utf-8";','')
      with open("../data/" + f, "w", encoding="utf8") as js_new:
        js_new.write(js_minified)
 
    if ext == ".html":
      print(f + " ... HTML")  
      html_minified = html_minify(web_raw).replace('@charset "utf-8";','')
      with open("../data/" + f, "w", encoding="utf8") as html_new:
        html_new.write(html_minified)
 
    if ext == ".svg":
      print(f + " ... SVG")
      shutil.copy2(f, '../data/' + f)

