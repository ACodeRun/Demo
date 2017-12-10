from math import log

def calcShannonEnt(dataSet):
    numEntries = len(dataSet)
    lableCounts = {}
    for featVec in dataSet:
        currentLable = featVec[-1]
        if currentLable not in lableCounts.keys():
            lableCounts[currentLable] = 0
        lableCounts[currentLable] += 1
    shannonEnt = 0
    for key in lableCounts:
        prob = float(lableCounts[key])/numEntries
        shannonEnt -= prob * log(prob,2)
    return shannonEnt
    
def createDataSet():
    dataSet = [[1,0,0,0,0,0,'fight'],[0,1,1,0,0,0,'fight2'],[0,1,0,1,1,0,'fight3']]
    lables = ['weapon','bullet','blood','123','313','14114']
    return dataSet,lables

def splitDataSet(dataSet,axis,value):
    retDataSet = []
    for featVec in dataSet:
        if featVec[axis] == value:
            reducedFeatVec = featVec[:axis]
            reducedFeatVec.extend(featVec[axis+1:])
            retDataSet.append(reducedFeatVec)
    return retDataSet

def chooseBestFeatureToSplit(dataSet):
    numlist = []
    numFeatures = len(dataSet[0]) - 1
    baseEntropy = calcShannonEnt(dataSet)
    bestInfoGain = 0
    bestFeature = -1
    for i in range(numFeatures):
        featList = [example[i] for example in dataSet]
        uniqueVals = set(featList)
        newEntropy = 0
        for value in uniqueVals:
            subDataSet = splitDataSet(dataSet,i,value)
            prob = len(subDataSet)/float(len(dataSet))
            newEntropy += prob * calcShannonEnt(subDataSet)
        infoGain = baseEntropy - newEntropy
        #numlist.append([infoGain,i])
        if (infoGain > bestInfoGain):
            bestInfoGain = infoGain
            bestFeature = i
    return bestFeature
    #return numlist

def createTree(dataSet,lables):
    classList = [example[-1] for example in dataSet]
    if classList.count(classList[0]) == len(classList):
        return classList[0]
    if len(dataSet[0]) == 1:
        return majorityCnt(classList)
    bestFeat = chooseBestFeatureToSplit(dataSet)
    bestFeatLable = lables[bestFeat]
    myTree = {bestFeatLable:{}}
    del(lables[bestFeat])
    featValues = [example[bestFeat] for example in dataSet]
    uniqueVals = set(featValues)
    for value in uniqueVals:
        subLables = lables[:]
        myTree[bestFeatLable][value] = createTree(splitDataSet(dataSet,bestFeat,value),subLables)
    return myTree

def majorityCnt(classList):
    classCount = {}
    for vote in classList:
        if vote not in classCount.keys():classCount[vote] = 0
        classCount[vote] += 1
    sortedClassCount = sorted(classCount.iteritems(),key = operator.itemgetter(1),reverse=True)
    return sortedClassCount[0][0]

myDat,lable = createDataSet()
#datalist = chooseBestFeatureToSplit(myDat)
#for i in datalist:
    #print i

print createTree(myDat,lable)
