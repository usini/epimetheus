from css_html_js_minify import html_minify, css_minify
from jsmin import jsmin
import os

def convertToGZIP(filename, varname, new_filename):

  with open(filename, 'r') as index_file:
    index_raw = index_file.read()

  # Minize file
  ext = os.path.splitext(filename)[1]

  if ext == ".css":
    print(filename + " ... " + " CSS")
    index_minified = css_minify(index_raw)
  elif ext == ".js":
    print(filename + " ... " + " JS")
    index_minified = jsmin(index_raw)
  else:
    print(filename + " ... " + " HTML")
    index_minified = html_minify(index_raw)
    index_minified = css_minify(index_minified)
    index_minified = jsmin(index_minified)
    index_minified = index_minified.replace('@charset"utf-8";','')

  #print("--")
  #print(index_minified)
  # Save Minize file to tempory file
  with open(filename + ".min",'w') as index_min_file:
    index_min_file.write(index_minified)

  # Remove gz file if exists
  try:
    os.unlink(filename + ".min.gz")
  except:
    pass

  # Compress file (need gzip)
  try:
    os.system('gzip ' + filename + ".min")
  except:
    pass

  # Remove minimize file 
  try:
    os.unlink(filename + ".min")
  except:
    pass

  # Generate hex_str
  hex_str = "const char " + varname + "[] PROGMEM={"
  with open(filename + ".min.gz", 'rb') as f:
      block = f.read()
      for ch in block:
            hex_str += hex(ch) + ", "

  try:
    os.unlink(filename + ".min.gz")
  except:
    pass

  index_final = hex_str + "};"
  with open(new_filename,'w') as index_final_file:
    index_final_file.write(index_final)

convertToGZIP("index.html", "HTML_INDEX", "../html_index.h")
convertToGZIP("style.css", "CSS_STYLE", "../css_style.h")
convertToGZIP("charts.css", "CSS_CHARTS", "../css_charts.h")
convertToGZIP("index.js", "JS_INDEX", "../js_index.h")
convertToGZIP("charts.js", "JS_CHARTS", "../js_charts.h")
print("... Done!")