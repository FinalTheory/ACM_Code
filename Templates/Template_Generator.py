import os

def _smartcode(stream):
	try:
		ustring = unicode(stream, 'gb2312')
	except UnicodeDecodeError:
		ustring = unicode(stream, 'utf8')
	return ustring.encode("gb2312")

def _appendcode(root, sth):
	fp = open(root+"\\"+sth)
	allines = fp.readlines()
	fp.close
	fw.write("qwerty\n## " + sth + "\n")
	for eachline in allines:
		fw.write("    " + _smartcode(eachline))
	fw.write("\n")

dir = "Z:\Templates"
filename = "Templates.md"
fw = open(filename,"w")
for root, dirs, files in os.walk(dir):
	for sth in files:
		open(filename, 'a').write("%s %s %s" % (root,dirs,sth))
		_appendcode(root, sth)
fw.close()
