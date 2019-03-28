# -*- coding:utf-8 -*-

import sys, json, pdb

reload(sys)
sys.setdefaultencoding('utf-8')

kDictpath = "/tmp/mob.txt"
kSep = "\t"
kColName = [
        "name", 
        "pos", 
        "shape", 
        "pinyin", 
        "notionOrForm", 
        "nominalOrPredicate",
        "singleOrCompound"]

def filelinePreprocess(line) :
    if line[-1] == '\n' :
        line = line[:-1]

    if line[-1] == '\r' :
        line = line[:-1]
    return line    

def createDictItemFromLine(items) :
    dictItem = {}
    dictItem[kColName[1]] = items[1]
    dictItem[kColName[2]] = items[2]
    dictItem[kColName[3]] = items[3]

    if items[4] == "实" :
        dictItem[kColName[4]] = "notion"
    elif items[4] == "虚" :
        dictItem[kColName[4]] = "form"
    else :    
        dictItem[kColName[4]] = "other"

    if items[5] == "体" :
        dictItem[kColName[5]] = "nominal"
    elif items[5] == "谓" :
        dictItem[kColName[5]] = "predicate"
    else :    
        dictItem[kColName[5]] = "other"

    if items[6] == "单" :
        dictItem[kColName[6]] = "single"
    else :    
        dictItem[kColName[6]] = "other"
    return dictItem

def process(theDict, line) :
    items = filelinePreprocess(line).split(kSep)
    assert len(items) == len(kColName)

    processed = []    
    for item in items :
        if len(item) >= 2 and item[0] == '"' and item[len(item) - 1] == '"' :
            processed += [item[1 : len(item) - 1]]
        else :
            processed += [item]

    dictItem = createDictItemFromLine(processed)
    name = processed[0]
    if name in theDict.keys() :
        theDict[name] += [dictItem]
    else :    
        theDict[name] = [dictItem]

if __name__ == "__main__" :
    theDict = {}
    cnt = 0
    for line in open(kDictpath) :
        process(theDict, line)
        cnt += 1
    print(json.dumps(theDict, ensure_ascii=False))
